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
#include "hacks/xpos.hpp"


#define X_POS_NEW 1*(10**37)

void insta_complete(HANDLE hProc);