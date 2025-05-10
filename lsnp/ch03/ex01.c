#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  struct stat statbuf;

  if (argc < 2) {
    perror("argc");
    exit(1);
  }

  if (lstat(argv[1], &statbuf) < 0) {
    perror("stat");
    exit(1);
  }

  if (S_ISREG(statbuf.st_mode) != 0) {
    printf("%d\n", statbuf.st_mode);
    printf("S_ISREG\n");
  } else if (S_ISLNK(statbuf.st_mode) != 0) {
    printf("%d\n", statbuf.st_mode);
    printf("S_ISLNK\n");
  } else if (S_ISDIR(statbuf.st_mode) != 0) {
    printf("%d\n", statbuf.st_mode);
    printf("S_ISDIR\n");
  } else if (S_ISBLK(statbuf.st_mode) != 0) {
    printf("%d\n", statbuf.st_mode);
    printf("S_ISBLK\n");
  } else if (S_ISFIFO(statbuf.st_mode) != 0) {
    printf("%d\n", statbuf.st_mode);
    printf("S_ISFIFO\n");
  } else if (S_ISCHR(statbuf.st_mode) != 0) {
    printf("%d\n", statbuf.st_mode);
    printf("S_ISCHR\n");
  } else if (S_ISSOCK(statbuf.st_mode) != 0) {
    printf("%d\n", statbuf.st_mode);
    printf("S_ISSOCK\n");
  }

  return 0;
}
