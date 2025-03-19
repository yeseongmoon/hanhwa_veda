#include <stdio.h>

int main(int argc, char *argv[]) {
  char ch = 'A';
  char ch1 = 'C';
  // const pointer can be used differently depending on the location of const
  // keyword
  const char *const ptr = &ch;
  printf("*ptr: %c\n", *ptr);
  // *ptr = 'B';
  printf("*ptr: %c\n", *ptr);
  // ptr = &ch1;

  return 0;
}
