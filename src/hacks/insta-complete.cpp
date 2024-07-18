#include "hacks/insta-complete.hpp"

int pow(int a, int b){
  int res = a;
  for(int i = 1; i < a; i++)
    res *= b;
  return res;
}

float get_end(){
  return 1 * pow(10,10);
}


void insta_complete(HANDLE hProc){
  uintptr_t base = getBase(getProc(_T("GeometryDash.exe")));
  std::vector<DWORD> offsets = playerdata_offsets[0];
  uintptr_t baseAddr = 0;
  bool r = ReadProcessMemory(hProc, (LPVOID)(base+PLAYERPTR),
                          &baseAddr, sizeof(baseAddr), NULL);

  if(!r) return;
  uintptr_t address = resolvePtrChain(hProc, baseAddr, offsets);
  writeFloat(hProc, address, get_end());
}