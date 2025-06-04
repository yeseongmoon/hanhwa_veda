#include "sk_ioctl.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>

int main(void) {
  int retn;
  int fd;

  int flag = 0;

  /* write에서 사용할 버퍼 */
  char buf[100] = {0};
  fd = open("/dev/SK", O_RDWR);
  printf("fd = %d\n", fd);
  if (fd < 0) {
    perror("/dev/SK error");
    exit(-1);
  } else
    printf("SK has been detected...\n");
  /* fd가 가르키는 파일에 buf에 있는 10바이트를 쓰라는 의미 */

  int choice;
  printf("1. UP 2. DOWN\n");
  printf("--> ");
  scanf("%d", &choice);
  if (choice == 1) {
    ioctl(fd, SPEED_UP, 0);
  } else {
    ioctl(fd, SPEED_DOWN, 0);
  }

  close(fd);
  return 0;
}
