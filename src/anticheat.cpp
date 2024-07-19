#include "anticheat.hpp"

std::vector<uint8_t> ac_backup; // length 33
std::vector<uint8_t> ac_disable = {
  0x90, 0x90, 0x90, 0x90, 0x90, 0x90
};

bool status = false;
bool anticheat_on(HANDLE hProc){
  uint8_t buffer[33];
  bool res = readMem(hProc, OFFSET, buffer, 33);
  if(res && buffer[0] == 0x90){
    std::cout << "[-] Anticheat already on!\n";
    status = true;
    return true;
  } else if(res && buffer[0] != 0x90){
    std::cout << "[-] Anticheat is off.\n";
    for(int i = 0; i < 33; i++)
      ac_backup.push_back(buffer[i]);
  }
  status = false;
  return false;
}

void set_anticheat(HANDLE hProc){
  switch(status){
    case false: // Off, turn it on.
      writeMem(hProc, OFFSET, ac_disable);
      status = true;
      break;
    
    case true: // On, turn it off.
      writeMem(hProc, OFFSET, ac_disable);
      status = false;
      break;
  }
}