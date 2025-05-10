#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  struct stat statbuf;

  system("touch data; ls -l data");
  stat("data", &statbuf);
  printf("\nchmod()\n");
  chmod("data", statbuf.st_mode | S_IXUSR | S_IXGRP);
  system("ls -l data");
  link("data", "data1");
  symlink("data", "data2");
  printf("\nlink() & symlink()\n");
  system("ls -li data data1 data2");

  return 0;
}
