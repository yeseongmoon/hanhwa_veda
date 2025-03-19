#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char *argv[]) {
  double dnum[2][3];
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      scanf("%lf", &dnum[i][j]);
    }
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%.3lf ", dnum[i][j]);
    }
  }
  printf("\n");

  return 0;
}
