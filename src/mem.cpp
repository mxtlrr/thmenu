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

uintptr_t resolvePtrChain(HANDLE hProc, uintptr_t starting, std::vector<DWORD> offsets){
	uintptr_t res = starting;
	for(int i =0; i < offsets.size()-1;i++){
		bool r = ReadProcessMemory(hProc, (LPCVOID)(res+offsets[i]), &res,
									sizeof(res), NULL);
		if(!r){
			return 0;
		} else {
			// std::cout << "[internal] Reading from 0x" << std::hex << (res + offsets[i])
			// 		<<" | Got: 0x" << res << std::dec << std::endl;
		}
	}

	res += offsets.back();
	return res;
}

bool readFloat(HANDLE hProc, DWORD_PTR addr, float& val) {
	return ReadProcessMemory(hProc, reinterpret_cast<LPCVOID>(addr),
									&val, sizeof(val), nullptr);
}

bool writeFloat(HANDLE hProc, DWORD_PTR addr, float val) {
	return WriteProcessMemory(hProc, reinterpret_cast<LPVOID>(addr),
									&val, sizeof(val), nullptr);
}