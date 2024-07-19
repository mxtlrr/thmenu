#include <thread>
#include <atomic>

#include "hacks/xpos.hpp"

std::atomic<bool> stop_thread(false);
void xpos_stop(HANDLE hProc, struct hack_offset x){
  // Get current x position 
  float curX = getVal(hProc, x);
  while(!stop_thread.load()){
    // TODO: check if we're in platformer mode
    // and modify accordingly.

    writeVal(hProc, x, curX-4);
    // TODO: maybe wait something?
  }
}


struct hack_offset init_xposhack(HANDLE hProc, uintptr_t base){
  struct hack_offset x; x.enabled = false; x.index = 1;
  x.offsets = playerdata_offsets[0];
  uintptr_t baseAddr = 0;
  bool r = ReadProcessMemory(hProc, (LPVOID)(base+PLAYERPTR),
                              &baseAddr, sizeof(baseAddr), NULL);
  if(!r){
    x.resolvedAddress = 0x00;
    return x;
  }
  x.resolvedAddress = resolvePtrChain(hProc, baseAddr, x.offsets);

  return x;
}

std::thread gc_thread;
void toggle_xpos_freeze(HANDLE proc, struct hack_offset x){
  if(x.index != 1) return;

  switch(hacks[x.index]){
    case true:
      if(gc_thread.joinable()){
        stop_thread.store(true);
        gc_thread.join();
        printf("[:)] Stopping X-Pos freeze.\n");
      }
      set_status(x.index, false);
      break;

    case false:
      // start thread
      if(!gc_thread.joinable()){
        stop_thread.store(false);
        gc_thread = std::thread(xpos_stop, proc, x);
        printf("[...] Starting X-Pos freeze!\n");
      }
      set_status(x.index, true);
      break;
  }
}

bool writeVal(HANDLE proc, struct hack_offset x, float value){
  return writeFloat(proc, x.resolvedAddress, value);
}

float getVal(HANDLE proc, struct hack_offset x){
  float k = 0.0f;
  bool z = readFloat(proc, x.resolvedAddress, k);
  if(!z) return -1.0f;
  else return k;
}