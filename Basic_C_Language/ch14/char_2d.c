#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char *argv[]) {
  char names[5][20];
  int count = sizeof(names) / sizeof(names[0]);
  int i;

  for (i = 0; i < count; i++) {
    fgets(names[i], 20, stdin);
    // get rid of 'enter'
    names[i][strlen(names[i]) - 1] = '\0';
  }
  printf("\n");

  for (i = 0; i < count; i++) {
    printf("%s", names[i]);
    printf("\n");
  }

  char s_name[20];
  printf("search name? ");
  fgets(s_name, 20, stdin);
  s_name[strlen(s_name) - 1] = '\0';

  for (i = 0; i < count; i++) {
    if (strcmp(s_name, names[i]) == 0) {
      printf("Name found on %dth on the array.\n", i + 1);
      break;
    }
  }
  if (i == 5) {
    printf("Name not found\n");
  }

  return 0;
}
