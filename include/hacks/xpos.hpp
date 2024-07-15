#pragma once

#include <iostream>
#include <vector>
#include <cstdint>

#include "mem.hpp"
#include "process.hpp"
#include "hack.hpp"
#include "offsets.hpp"

/* TODO: reimplement hack.hpp so that this is in the hack struct,
 * or at least it's own struct there. */
struct xpos_hack {
  uintptr_t resolvedAddress;      // Resolved pointer chain address.
  bool enabled;
  int index;
};

struct xpos_hack init_xposhack(HANDLE hProc, uintptr_t base);
void toggle_hack(HANDLE proc, struct xpos_hack x);

/* TODO: function to freeze xposition of player, should be in its own
 * thread. */

// Note that if you are not using this in platformer, then you should call
// the function with the desired X position minus 4, i.e. if I want
// X=50, then I pass in 54.
bool writeVal(HANDLE proc, struct xpos_hack x, float value);

// Returns -1.0f on failure.
float getVal(HANDLE proc, struct xpos_hack x);