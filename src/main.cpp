#include <iostream>
#include <windows.h>

#include "process.hpp"
#include "mem.hpp"

extern "C" {
	#include <psapi.h>
}

int main(void){
	std::cout << "[+] Looking for GeometryDash...";
	DWORD processId = getProc(_T("GeometryDash.exe"));
	if(processId != 0){
		std::cout << "found! PID=" << processId << std::endl;
	} else {
		std::cout << "not running!\n";
		return 1;
	}
	uintptr_t guh = getBase(processId);
	std::cout << "[+] Base located at 0x" << std::hex << guh << std::dec << std::endl;
}