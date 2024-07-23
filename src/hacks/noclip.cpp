#include "hacks/noclip.hpp"

std::vector<uint8_t> backup;

struct hack_noffset init_noclip(HANDLE hProc){
  struct hack_noffset noclip;

  // Generate a backup
  uint8_t buffer_cont[51];
	std::vector<uint8_t> backup;
	std::cout << "[...] Storing 0x3905f3 contents as backup...\n";
	bool res = readMem(hProc, NOCLIP_LOCATION, buffer_cont, 51);
  if(buffer_cont[0] == 0x90){
    // Bad! making a backup is useless.
    printf("[:(] Sorry, THMenu can't continue. Noclip seems to be already enabled.\n");
    printf("Please restart your game.\n");
    exit(1);

    // Return null struct. We shouldn't get this far anyways.
    return noclip;
  }
	if(res){
		for(int i = 0; i < 51; i++)
      backup.push_back(buffer_cont[i]);
  }

	noclip.address = NOCLIP_LOCATION; noclip.name = "Noclip";
	noclip.opcodes = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
	noclip.index   = 0; noclip.replace_by = backup; noclip.enabled = false;
  return noclip;
}

void toggle_noclip(HANDLE proc, struct hack_noffset ctx){
  if(ctx.index != 0) return; // What the fuck are you doing?

  switch(hacks[ctx.index]){
    case true:
      writeMem(proc, ctx.address, ctx.replace_by);
      set_status(ctx.index, false);
      break;
    
    case false:
      writeMem(proc, ctx.address, ctx.opcodes);
      set_status(ctx.index, true);
      break;
  }
}