#include "hacks/xpos.hpp"

struct xpos_hack init_xposhack(HANDLE hProc, uintptr_t base){
  struct xpos_hack x; x.enabled = false; x.index = 1;
  // Resolve the pointer chain
  std::vector<DWORD> offsets{0x208, 0xd98, 0xc10, 0xd8, 0xd8, 0xa90};
  uintptr_t baseAddr = 0;
  bool r = ReadProcessMemory(hProc, (LPVOID)(base+PLAYERPOS_X),
                              &baseAddr, sizeof(baseAddr), NULL);
  if(!r){
    x.resolvedAddress = 0x00;
    return x;
  }
  x.resolvedAddress = resolvePtrChain(hProc, baseAddr, offsets);

  return x;
}

void toggle_hack(HANDLE proc, struct xpos_hack x){
  if(x.index != 1) return;

  switch(hacks[x.index]){
    case true:
      // ...
      set_status(x.index, false);
      break;

    case false:
      // ...
      set_status(x.index, true);
      break;
  }
}

bool writeVal(HANDLE proc, struct xpos_hack x, float value){
  return writeFloat(proc, x.resolvedAddress, value);
}

float getVal(HANDLE proc, struct xpos_hack x){
  float k = 0.0f;
  bool z = readFloat(proc, x.resolvedAddress, k);
  if(!z) return -1.0f;
  else return k;
}