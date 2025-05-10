#include <stdio.h>

void func(void);

int main(int argc, char *argv[]) {
  printf("Compile date & time : %s, %s\n", __DATE__, __TIME__);
  printf("file name : %s\n", __FILE__);
  printf("function name: %s\n", __FUNCTION__);
  printf("line number: %d\n", __LINE__);

#line 100 "macro.c"
  func();
  return 0;
}

void func(void) {
  printf("Compile date & time : %s, %s\n", __DATE__, __TIME__);
  printf("file name : %s\n", __FILE__);
  printf("function name: %s\n", __FUNCTION__);
  printf("line number: %d\n", __LINE__);
}
