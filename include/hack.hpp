#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <windows.h>

/* This structure refers to a hack, whether that be noclip,
 * or something else. Members:
 * -> Address: This is the address that the modification is at. */
struct hack {
  std::string name;    // Name of the hack.
  uint64_t address;    /* Independent of base, i.e. for noclip this 
                        * would be 0x3905f3. */
  std::vector<uint8_t> opcodes; // The opcode that will be modified.
  int index;           // The index of said hack in a list
  bool enabled;        // Is the hack working right now?

  /* Optional field(s) */
  std::vector<uint8_t> replace_by; // When the hack is turned off, code
                                   // will be called to replace opcodes by replace_by.
};

// A list of if each hack is toggled or not. This is probably a really
// bad way to do this. Order:
// 0th - Noclip.
extern bool hacks[];

// Toggle a hack
struct hack toggle_hack(struct hack h);

// Is a hack currently on? Return value:
//    True  -- Yes.
//    False --  No. 
bool get_status_of_hack(int index);
void set_status(int index, bool new_val);