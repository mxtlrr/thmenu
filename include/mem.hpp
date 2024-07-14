#pragma once
#include <windows.h>
#include <iostream>
#include <cstdint>
#include <vector>

// Open a process for reading and writing to memory
HANDLE openProc(DWORD pid);

// Read memory at address into buffer
bool readMem(HANDLE proc, uintptr_t address, void* buffer, SIZE_T size);

// credit: lilcloxy on unknowncheats.me, modified a bit to fix
// some issues.
bool writeMem(HANDLE proc, DWORD pid, uintptr_t const addr, std::vector<unsigned char> const& bytes);