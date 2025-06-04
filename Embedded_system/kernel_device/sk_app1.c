/***************************************
 * Filename: sk_app.c
 * Title: Skeleton Device Application
 * Desc: Implementation of system call
 ***************************************/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) {
  int fd;
  fd = open("/dev/SK", O_RDWR);
  printf("fd = %d\n", fd);
  if (fd < 0) {
    perror("/dev/SK error");
    exit(-1);
  } else
    printf("SK has been detected...\n");
  close(fd);
  return 0;
}
