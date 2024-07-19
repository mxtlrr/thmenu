#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <windows.h>

/* This structure refers to a hack, whether that be noclip,
 * or something else. Members:
 * -> Name:       Name of the hack
 * -> Address:    This is the address that the modification is at. 
 * -> Opcodes:    Opcodes to change it to
 * -> Index:      Index of hack in hacks.
 * -> Enabled:    Is this hack enabled?
 * -> Replace_by: ...
 * Note that this hack requires the hack to not have an offset,
 * and be it's own specific address */
struct hack_noffset {
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

/* Same as above but this assumes the hack has an offset, and is not at a
 * specific address. Members:
 * -> Offsets:          offsets to the hack
 * -> ResolvedAddress:  address after the offset stuff
 * -> Enabled:          hack enabled?
 * -> Index:            index of hack.
 * */
struct hack_offset {
  std::vector<DWORD> offsets;
  uintptr_t resolvedAddress;
  bool enabled;
  int index; 
};

// A list of if each hack is toggled or not. This is probably a really
// bad way to do this. Order:
// 0th - Noclip.
extern bool hacks[];

// Toggle a hack
struct hack_noffset toggle_hack(struct hack_noffset h);

// Is a hack currently on? Return value:
//    True  -- Yes.
//    False --  No. 
bool get_status_of_hack(int index);
void set_status(int index, bool new_val);