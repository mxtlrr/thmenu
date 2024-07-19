#include "hack.hpp"

bool hacks[] = {
  false,       // Noclip
  false,       // X-Position bypass
  false        // No-Rotate
};

bool get_status_of_hack(int index){
  return hacks[index];
}

void set_status(int index, bool new_val){
  hacks[index] = new_val;
}

struct hack_noffset toggle_hack(struct hack_noffset h){
  // Might be a really stupid way of doing this.
  struct hack_noffset new_h = h;
  new_h.enabled = !h.enabled; // true => false, vice versa.
  return new_h;
}