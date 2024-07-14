#include "process.hpp"

DWORD getProc(const TCHAR* processName) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		std::cerr << "[!] CreateToolhelp32Snapshot failed: " << GetLastError() << std::endl;
		return 0;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapshot, &pe)) {
		do {
			if (_tcsicmp(pe.szExeFile, processName) == 0) {
				CloseHandle(hSnapshot);
				return pe.th32ProcessID;
			}
		} while (Process32Next(hSnapshot, &pe));
	}

	CloseHandle(hSnapshot);
	return 0;
}