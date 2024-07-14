#include <iostream>
#include <windows.h>

#include "process.hpp"
#include "offsets.hpp"
#include "mem.hpp"

#include "hack.hpp"
#include "hacks/noclip.hpp"

#define ARR_LENGTH(x) (sizeof(x)/(sizeof(x[0])))

int main(void){
	std::cout << "[+] Looking for GeometryDash...";
	DWORD processId = getProc(_T("GeometryDash.exe"));
	HANDLE hProc = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processId);
	if(processId != 0){
		std::cout << "found! PID=" << processId << std::endl;
	} else {
		std::cout << "not running...\n";
		return 1;
	}
	uintptr_t guh = getBase(processId);
	std::cout << "[+] Base located at 0x" << std::hex << guh << std::dec << std::endl;

	int b; bool running = true;
	struct hack nc = init_noclip(hProc);

	while(running){
		printf("> ");
		std::cin >> b;

		switch(b){
			case 0: // toggle noclip.
				printf("Toggling noclip...");
				toggle_noclip(hProc, nc);
				printf("%s\n", get_status_of_hack(0) ? "On!" : "Off.");
				break;

			case 3:
				running = false;
				break;
		}
	}

	CloseHandle(hProc);
	return 0;
}