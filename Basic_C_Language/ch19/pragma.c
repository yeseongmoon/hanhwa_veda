#include <stdio.h>

#pragma pack(push, 1)
typedef struct {
  char ch;
  int in;
} Sample1;

#pragma pack(pop)
typedef struct {
  char ch;
  int in;
} Sample2;

int main(int argc, char *argv[]) {
  printf("size of struct Simple1: %lubyte\n", sizeof(Sample1));
  printf("size of struct Simple2: %lubyte\n", sizeof(Sample2));
  return 0;
}
