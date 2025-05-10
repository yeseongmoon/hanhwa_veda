#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n;
  printf("Size: ");
  scanf("%d", &n);
  int *p = (int *)calloc(n, sizeof(int) * n);
  int **ptr = &p;
  for (int i = 0; i < n; i++) {
    scanf("%d", p + i);
  }

  for (int i = 0; i < n; i++) {
    printf("*p: %d ", p[i]);
  }
  printf("\n");

  for (int i = 0; i < n; i++) {
    printf("**p: %d ", **ptr + i);
  }
  printf("\n");

  p = (int *)realloc(p, sizeof(int) * n * 2);
  printf("Realloc for double size\n");

  for (int i = n; i < n * 2; i++) {
    scanf("%d", p + i);
  }

  for (int i = 0; i < n * 2; i++) {
    printf("*p: %d ", p[i]);
  }
  printf("\n");

  for (int i = 0; i < n * 2; i++) {
    printf("**p: %d ", **ptr + i);
  }
  printf("\n");

  free(p);

  return 0;
}
