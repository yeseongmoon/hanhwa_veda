#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char *argv[]) {
  char names[5][20];
  int count = sizeof(names) / sizeof(names[0]);

  for (int i = 0; i < count; i++) {
    fgets(names[i], 20, stdin);
    names[i][strlen(names[i]) - 1] = '\0';
  }
  printf("\n");

  for (int i = 0; i < count; i++) {
    for (int j = 0; j < strlen(names[i]); j++) {
      printf("%c", names[i][j]);
    }
    printf("\n");
  }

  return 0;
}
