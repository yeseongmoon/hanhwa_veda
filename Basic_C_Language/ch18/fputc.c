#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  /*FILE *fp;*/
  /*char str[] = "banana";*/
  /*int i;*/
  /**/
  /*fp = fopen("b.txt", "w");*/
  /*if (fp == NULL) {*/
  /*  printf("파일을 만들지 못했습니다.\n");*/
  /*  return 1;*/
  /*}*/
  /*i = 0;*/
  /*while (str[i] != '\0') {*/
  /*  fputc(str[i], fp);*/
  /*  i++;*/
  /*}*/
  /*fputc('\n', fp);*/
  /*fclose(fp);*/
  /**/
  /*fp = fopen("b.txt", "r");*/
  /**/
  /*if (fp == NULL) {*/
  /*  printf("파일을 찾지 못했습니다.\n");*/
  /*}*/
  /**/
  /*char output;*/
  /*while (1) {*/
  /*  output = fgetc(fp);*/
  /*  if (output == EOF)*/
  /*    break;*/
  /*  putchar(output);*/
  /*}*/
  /*fclose(fp);*/

  FILE *ifp;
  char str[20];

  ifp = fopen("b.txt", "r");
  if (ifp == NULL) {
    printf("Failed to open the file\n");
  }

  while (fgets(str, sizeof(str), ifp) != NULL) {
    printf("%s", str);
  }

  return 0;
}
