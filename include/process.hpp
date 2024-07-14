#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>
#include <Psapi.h>

#define TH32CS_SNAPMODULE32 0x00000010


DWORD getProc(const TCHAR* processName);
uintptr_t getBase(DWORD procId);