#pragma once

#include <iostream>
#include <vector>
#include <cstdint>

#include "mem.hpp"
#include "process.hpp"
#include "hack.hpp"
#include "offsets.hpp"

struct hack_offset init_xposhack(HANDLE hProc, uintptr_t base);
void toggle_xpos_freeze(HANDLE proc, struct hack_offset x);

// Note that if you are not using this in platformer, then you should call
// the function with the desired X position minus 4, i.e. if I want
// X=50, then I pass in 54.
bool writeVal(HANDLE proc, struct hack_offset x, float value);

// Returns -1.0f on failure.
float getVal(HANDLE proc, struct hack_offset x);