#include <stdio.h>

#define VER 7
#define BIT16

int main(int argc, char *argv[]) {
  int max;

#if VER >= 6
  printf("version %d\n", VER);
#endif

#ifdef BIT16
  max = 32767;
#else
  max = 2147483647;
#endif

  printf("max integer value is : %d\n", max);

  return 0;
}
