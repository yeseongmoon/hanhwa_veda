// #include "static.h"
#include "shared.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("main start\n");
  // static_function(100);
  shared_function(100, 200);
  printf("main end\n");
  return 0;
}
