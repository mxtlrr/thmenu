#include "mem.hpp"
#include "process.hpp"

bool writeMem(HANDLE proc, uintptr_t const addr, std::vector<uint8_t> const& bytes){
	// Update uintptr with base, so we don't get E998.
	uintptr_t base = getBase(getProc(_T("GeometryDash.exe")));
	bool f = WriteProcessMemory(proc, reinterpret_cast<LPVOID>(base+addr), bytes.data(),
					bytes.size(), nullptr);
	if(!f) {
		std::cout << "[INTERNAL] E code -> " << GetLastError() << std::endl;
		return false;
	}
	return true;
}

bool readMem(HANDLE proc, uintptr_t address, void* buffer, SIZE_T size) {
	SIZE_T bytesRead;
	uintptr_t base = (getBase(getProc(_T("GeometryDash.exe"))));
	return ReadProcessMemory(proc, (LPCVOID)(base+address), buffer, size, &bytesRead) && bytesRead == size;
}