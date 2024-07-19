#include "hacks/no-rotate.hpp"

uintptr_t nr_get_address(HANDLE hProc){
  uintptr_t base = getBase(getProc(_T("GeometryDash.exe")));
  std::vector<DWORD> offsets = playerdata_offsets[2];

  uintptr_t baseAddr = 0;
  bool r = ReadProcessMemory(hProc, (LPVOID)(base+PLAYERPTR),
                          &baseAddr, sizeof(baseAddr), NULL);

  if(!r) return 0;
  else return resolvePtrChain(hProc, baseAddr, offsets);
}

std::atomic<bool> stop_thread_nr(false);
void nr_stop(HANDLE hProc){
  uintptr_t z = nr_get_address(hProc);
  float z2 = 0.0f;
  readFloat(hProc, z, z2);

  while(!stop_thread_nr.load())
    writeFloat(hProc, z, z2);
}

std::thread gc_thread_nr;
void toggle_no_rotate(HANDLE hProc){
  switch(hacks[2]){
    case true:
      if(gc_thread_nr.joinable()){
        stop_thread_nr.store(true);
        gc_thread_nr.join();
        printf("Stopped No-rotate.\n");  
      }
      set_status(2,false);
      break;
    
    case false:
      if(!gc_thread_nr.joinable()){
        stop_thread_nr.store(false);
        gc_thread_nr = std::thread(nr_stop, hProc);
        printf("Started No-rotate.\n");
      }
      set_status(2,true);
      break;
  }
}