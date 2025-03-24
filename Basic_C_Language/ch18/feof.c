#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *fp = fopen("b.txt", "r");
  char str[20];
  if (fp == NULL) {
    fprintf(stderr, "File not existed.\n");
    return 1;
  }

  fseek(fp, 10, SEEK_SET);
  fgets(str, sizeof(str), fp);
  printf("%s\n", str);
  while (1) {
    fgets(str, sizeof(str), fp);
    if (feof(fp)) {
      break;
    }
    printf("%s\n", str);
  }
  fclose(fp);

  return 0;
}
