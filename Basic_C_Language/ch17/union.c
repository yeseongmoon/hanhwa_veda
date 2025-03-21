#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

union ipaddr {
  // order matters
  unsigned char each[4];
  unsigned int all;
};

int main(int argc, char *argv[]) {
  union ipaddr ip;
  ip.all = 0x12345678;
  printf("size %lu\n", sizeof(ip));
  printf("ip each: ");
  for (int i = 0; i < 4; i++) {
    printf("%x ", ip.each[i]);
  }
  printf("\n");
  printf("ip.all : %x\n", ip.all);
  return 0;
}
