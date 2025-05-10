#include "mem.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  MEM person;

  printf("main start\n");
  func1();
  func2(100);
  printf("main end\n");
  return 0;
}
