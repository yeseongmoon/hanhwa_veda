#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(int argc, char *argv[]) {
  /*int n = 100;*/
  /*char name[20] = "Hello";*/
  /*float f = 1.234;*/
  /**/
  /*FILE *fp;*/
  /**/
  /*fp = fopen("data.txt", "w");*/
  /*if (fp == NULL) {*/
  /*  printf("Failed to open.\n");*/
  /*  return 1;*/
  /*}*/
  /**/
  /*fprintf(fp, "%d %s %f\n", n, name, f);*/
  /*fclose(fp);*/

  int new_int;
  float new_float;
  char new_char[20];

  FILE *new_fp;
  new_fp = fopen("data.txt", "r");
  if (new_fp == NULL)
    printf("Failed to open\n");
  fscanf(new_fp, "%d%s%f", &new_int, new_char, &new_float);

  printf("%d %s %f\n", new_int, new_char, new_float);
  fclose(new_fp);

  return 0;
}
