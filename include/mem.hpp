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
bool writeMem(HANDLE proc, uintptr_t const addr, std::vector<unsigned char> const& bytes);


// Read a float to a memory address
bool readFloat(HANDLE hProc, DWORD_PTR addr, float& val);

// Write a float to a memory address
bool writeFloat(HANDLE hProc, DWORD_PTR addr, float val);


// Resolves a pointer chain.
// Input:
//    hProc    -> Handle to the program
//    starting -> The address where the address is
//                (this assumes you add the base address to it)
//    offsets  -> Pointer offsets
uintptr_t resolvePtrChain(HANDLE hProc, uintptr_t starting, std::vector<DWORD> offsets);