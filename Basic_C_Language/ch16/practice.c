#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int size = 5, input, count = 0;
  int *ptr = (int *)malloc(sizeof(int) * size);
  while (1) {
    printf("Enter a number(-1 for exit) : ");
    scanf("%d", &input);
    if (input == -1)
      break;
    if (count == size) {
      size += 10;
      ptr = (int *)realloc(ptr, sizeof(int) * size);
    }
    ptr[count] = input;
    count++;
  }
  for (int i = 0; i < count; i++) {
    printf("%d ", ptr[i]);
  }
  printf("\n");
  free(ptr);
  return 0;
}
