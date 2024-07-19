#include <iostream>
#include <windows.h>

#include "process.hpp"
#include "offsets.hpp"
#include "mem.hpp"
#include "anticheat.hpp"

#include "hack.hpp"
#include "hacks/noclip.hpp"
#include "hacks/xpos.hpp"
#include "hacks/no-rotate.hpp"
#include "hacks/insta-complete.hpp"

#include "cfg/readcfg.hpp"
#include "cfg/register_keys.hpp"

#define VERSION "0.1"

void quit(HANDLE hProc){
	deregister_keys();
	CloseHandle(hProc);
}

int main(void){
	std::cout << "[...] Reading config file" << std::endl;
	std::vector<uint32_t> keys = retrieve_keys("keys.cfg");

	// Now we can register those keybindings and then do something for it
	if(registerAllKeys(keys)) std::cout << "[:)] All keys registered.\n";
	// Internally, we also want to register 'Q', for cleaning everything up.
	RegisterHotKey(NULL, QUIT, MOD_NOREPEAT, 0x51);

	std::cout << "[+] Looking for GeometryDash...";
	DWORD processId = getProc(_T("GeometryDash.exe"));
	HANDLE hProc = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processId);
	if(processId != 0){
		std::cout << "found! PID=" << processId << std::endl;
	} else {
		std::cout << "not running...\n";
		quit(hProc);
		return 1;
	}
	uintptr_t base = getBase(processId);
	std::cout << "[+] Base located at 0x" << std::hex << base << std::dec << std::endl;

	bool running = true; bool ingame = true;
	struct hack_noffset nc = init_noclip(hProc);

	printf("[---] Welcome to THMenu v%s! Use your keybindings to toggle/enable hacks.\n",
					VERSION);

	struct hack_offset xa; // X-Pos offset
	MSG m;
	while(running){
		// Check if we're in the game.
		xa = init_xposhack(hProc, base);
		if(xa.resolvedAddress == 0) ingame = false;
		else ingame = true;

		BOOL msg_recv = PeekMessage(&m, NULL, 0, 0, PM_REMOVE);
		if(msg_recv != 0 && m.message == WM_HOTKEY){
			DWORD parameter = m.wParam;
			switch(parameter){
				case NOCLIP: // Noclip
					toggle_noclip(hProc, nc);
					printf("Noclip is now %s\n", get_status_of_hack(0) ? "on." : "off.");
					break;

				case XPOS_FR:
					if(ingame == true) toggle_xpos_freeze(hProc, xa);
					break;

				case NO_ROTA:
					if(ingame == true) toggle_no_rotate(hProc);
					break;

				case INSTACM:
					if(ingame == true && anticheat_on(hProc) == true) insta_complete(hProc);							
					else if(ingame == true && !(anticheat_on(hProc))){
						set_anticheat(hProc);			// Set anticheat to be on.
						insta_complete(hProc);		// Finish the level.
						set_anticheat(hProc);			// Turn it back off again.
					}
					printf("[+] Enjoy:)\n");
					break;

				case QUIT:
					// Don't cause some funky error, toggle off.
					if(get_status_of_hack(1) == true){
						toggle_xpos_freeze(hProc, xa);
						running = false;
					} else running = false;
					break;
			}
		}
	}

	std::cout << "Bye!" << std::endl;
	quit(hProc);
	return 0;
}