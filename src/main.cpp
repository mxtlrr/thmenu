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

	std::string b;

	struct hack nc = init_noclip(hProc);

	std::cout << "Type anything to turn on noclip!";
	std::cin >> b;

	toggle_noclip(hProc, nc);

	std::cout << "Type anything to turn off noclip!";
	std::cin >> b;

	CloseHandle(hProc);
	return 0;
}