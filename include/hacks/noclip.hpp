/* Noclip stuff. */
#pragma once

#include <iostream>
#include <vector>
#include <cstdint>

#include "mem.hpp"
#include "process.hpp"
#include "hack.hpp"
#include "offsets.hpp"

struct hack init_noclip(HANDLE hProc);
void toggle_noclip(HANDLE proc, struct hack ctx);