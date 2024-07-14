#include <iostream>
#include <windows.h>

#include "process.hpp"

int main(void){
	std::cout << "[+] Looking for GeometryDash...";
	DWORD processId = getProc(_T("GeometryDash.exe"));
	if(processId != 0){
		std::cout << "found! PID=" << processId << std::endl;
	} else {
		std::cout << "not running!\n";
		return 1;
	}


}