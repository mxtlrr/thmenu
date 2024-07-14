#include "mem.hpp"
#include "process.hpp"

bool writeMem(HANDLE proc, DWORD pid, uintptr_t const addr, std::vector<uint8_t> const& bytes){
    return WriteProcessMemory(proc, reinterpret_cast<LPVOID>(addr), bytes.data(),
            bytes.size(), nullptr);
}