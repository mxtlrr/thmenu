#include <iostream>
#include <windows.h>

#include "process.hpp"
#include "offsets.hpp"
#include "mem.hpp"

#include "hack.hpp"
#include "hacks/noclip.hpp"
#include "hacks/xpos.hpp"

#include "cfg/readcfg.hpp"
#include "cfg/register_keys.hpp"

#define ARR_LENGTH(x) (sizeof(x)/(sizeof(x[0])))

int main(void){
	std::cout << "[...] Reading config file" << std::endl;
	std::vector<uint32_t> keys = retrieve_keys("keys.cfg");

	// Now we can register those keybindings and then do something for it
	bool r = registerAllKeys(keys);
	if(r){
		std::cout << "[:)] All keys registered.\n";
	}

	// Internally, we also want to register 'Q', for cleaning everything up.
	RegisterHotKey(NULL, 26, MOD_NOREPEAT, 0x51);

	std::cout << "[+] Looking for GeometryDash...";
	DWORD processId = getProc(_T("GeometryDash.exe"));
	HANDLE hProc = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processId);
	if(processId != 0){
		std::cout << "found! PID=" << processId << std::endl;
	} else {
		std::cout << "not running...\n";
		deregister_keys();
		return 1;
	}
	uintptr_t guh = getBase(processId);
	std::cout << "[+] Base located at 0x" << std::hex << guh << std::dec << std::endl;

	int b; bool running = true;
	struct hack nc = init_noclip(hProc);

	struct xpos_hack xa = init_xposhack(hProc, guh);

	MSG m;
	while(running){
		BOOL msg_recv = GetMessage(&m, NULL, 0, 0);
		if(msg_recv != 0){
			if(m.message == WM_HOTKEY){
				DWORD parameter = m.wParam;
				switch(parameter){
					case 100: // Noclip
						toggle_noclip(hProc, nc);
						printf("Noclip is now %s\n", get_status_of_hack(0) ? "on." : "off.");
						break;

					case 200:
						// TODO: #2
						toggle_xpos_freeze(hProc, xa);
						break;

					case 26:
						running = false;
						break;
				}
			}
		}
	}

	// Clean up
	deregister_keys();
	CloseHandle(hProc);
	return 0;
}