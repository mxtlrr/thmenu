#pragma once

#include "mem.hpp"
#include "process.hpp"

#include <iostream>
#include <cstdint>
#include <windows.h>

#define OFFSET 0x384C08

// Checks if the anticheat is on or not.
bool anticheat_on(HANDLE hProc);
void set_anticheat(HANDLE hProc);

// Status of whether or not it's on or not
extern bool status;

// AC disable opcodes.
extern std::vector<uint8_t> ac_disable;