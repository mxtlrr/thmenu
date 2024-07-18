/* Locations of where certain things are in GeometryDash. These are
 * static variables, and hence, will not change. */
#pragma once

#include <vector>
typedef unsigned long DWORD;

#define NOCLIP_LOCATION 0x3905f3

/* Actually, it turns out that this is for all of the 
 * players, statistics. */
#define PLAYERPTR      0x687E10

extern std::vector<DWORD> playerdata_offsets[];