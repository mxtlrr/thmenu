/* Locations of where certain things are in GeometryDash. These are
 * static variables, and hence, will not change. */
#pragma once

#include <vector>
typedef unsigned long DWORD;

#define NOCLIP_LOCATION 0x3905f3

/* Actually, it turns out that this is for all of the 
 * players, statistics. */
#define PLAYERPTR      0x687E10

// Erm. It's bad to put code in a *.hxx file! :nerd:
std::vector<DWORD> playerdata_offsets[] = {
  {0x208,0xd98,0xc10,0xd8, 0xd8, 0xa90},       // X position
  {0x218,0xfc8,0xd8, 0x948,0x140,0xc00,0xa94}, // Y position
  {0x208,0xd98,0x740,0xd8, 0xd8, 0xd8, 0x38}   // rotation
};