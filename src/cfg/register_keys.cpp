#include "cfg/register_keys.hpp"

char keys_code[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,

  '1','2','3','4','5','6','7',
  '8','9',0,0,0,0,0,0,0,0,
  'A','B','C','D','E',
  'F','G','H','I','J','K','L','M',
  'N','O','P','Q','R','S','T','U',
  'V','W','X','Y','Z'
};

int ids[] = {
  100, 200, 300, 400
};


int iterator = 0;

bool registerAllKeys(std::vector<unsigned int> k){
  bool res = true;
  for(unsigned int vc : k){
    // We use MOD_NOREPEAT to not add some modifier like Alt, Ctrl, Win.
    if(vc == 0x51){
      printf("Sorry, I can't bind 'q' to something else. I'm not continuing.\n");
      return false;
    }
    BOOL g = RegisterHotKey(NULL, ids[iterator], MOD_NOREPEAT, vc);
    if(g) printf("[+] Registered 0x%x (%c) successfully to ID=%d\n", vc, keys_code[vc],
                ids[iterator]);

    iterator+=1;
  }
  return res;
}

void deregister_keys(){
  for(int i = ids[0]; i < (sizeof(ids)/(sizeof(ids[0]))); i+=100)
    UnregisterHotKey(NULL, i);
}