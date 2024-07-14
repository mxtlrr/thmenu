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



wchar_t *GetWC(char *c){
  const size_t cSize = strlen(c)+1;
  wchar_t* wc = new wchar_t[cSize];
  mbstowcs (wc, c, cSize);

  return wc;
}
uintptr_t getBase(DWORD procId){
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE){
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)){
			do {
				int fuckyou = wcscmp(GetWC(modEntry.szModule), L"GeometryDash.exe");
				if (!fuckyou){
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	} else {
		std::cout << "I couldn't -- E" << GetLastError() << std::endl;
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}