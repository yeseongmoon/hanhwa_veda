#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

typedef struct MEMBER {
  char name[20];
  int age;
} MEMBER;

int main(int argc, char *argv[]) {
  // this
  FILE *fp;
  MEMBER s1, s2;

  scanf("%s%d", s1.name, &s1.age);

  fp = fopen("member.txt", "wb");
  if (fp == NULL) {
    fprintf(stderr, "Failed to open the member.txt file\n");
  }

  fwrite(&s1, sizeof(MEMBER), 1, fp);

  fclose(fp);

  fp = fopen("member.txt", "rb");
  if (fp == NULL) {
    fprintf(stderr, "Failed to open the member.txt file\n");
  }
  fread(&s2, sizeof(MEMBER), 1, fp);

  printf("%s %d\n", s2.name, s2.age);
  fclose(fp);

  return 0;
}
