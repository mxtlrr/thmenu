#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <atomic>
#include <thread>

#include "mem.hpp"
#include "process.hpp"
#include "hack.hpp"
#include "offsets.hpp"

// Resolve the pointer address to the Rotation
// and return it. 
uintptr_t nr_get_address(HANDLE hProc);
void toggle_no_rotate(HANDLE hProc);
void nr_stop(HANDLE hProc);