#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>


DWORD getProc(const TCHAR* processName);
