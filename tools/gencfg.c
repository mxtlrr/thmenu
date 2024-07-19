#include <stdio.h>

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

int get_index(char c){
  int index = 0;
  for(int i = 0; i < 91; i++){
    if(keys_code[i] == c){
      index = i;
      return index;
    }
  }
  return 0;
}

char toUpper(char c){
  if(c >= 97 && c <= 122){
    return c-32;
  }
  return c;
}

int main(void){
  char m[4]     = {0};  // Array we use to generate config
  char input[5] = {0};  // Input from the user.

  printf("Welcome to gencfg. Enter a 4-character string, i.e. 4eb1 to generate\n");
  printf("a config from said keys.\n\n>> ");

  scanf("%s", input);

  for(int i = 0; i < 4; i++) m[i] = get_index(toUpper(input[i]));

  printf("[!] Finished generating. Write this in keys.cfg:\n");
  for(int i = 0; i < 4; i++){
    if(i != 3) printf("0x%x,", m[i]);
    else printf("0x%x\n", m[i]);
  }

  return 0;
}