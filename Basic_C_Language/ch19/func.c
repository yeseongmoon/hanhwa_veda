#include "mem.h"
#include <stdio.h>

void func1() {
  MEM p;
  printf("func1 called\n");
}
void func2(int num) {
  //
  printf("func2 called. num: %d\n", num);
}
