#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define KEY_NUM 4

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

char* hacks[] = {
  "Noclip         ",
  "X-pos freeze   ",
  "No rotation    ",
  "Insta complete "
};

// 4 keys, 3 commas plus a null terminator
uint8_t length = (KEY_NUM*4)+(KEY_NUM-1)+1;

int str_to_hex(char* s){
  char s2[3] = { s[2], s[3], 0 };
  int r = (int)strtol(s2, NULL, 16);
  return r;
}

int main(int argc, char** argv){
  if(argc != 2) {
    printf("usage: readcfg [file]\n");
    return 1;
  }
  char* file = argv[1];

  FILE* fp = fopen(file, "r");
  char data[100];
  fgets(data, length, fp);

  int index = 0;
  for(int i = 0; i < length; i+=5){
    // The hex code
    char zma[] = { data[i], data[i+1], data[i+2], data[i+3], 0 };
    int new_hex = str_to_hex(zma);
    printf("%s | Corresponds to the '%c' key.\n",
            hacks[index], keys_code[new_hex]);
    index++;
  }

  fclose(fp);
  return 0;
}