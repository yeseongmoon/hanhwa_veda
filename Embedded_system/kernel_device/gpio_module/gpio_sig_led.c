#include "sk_ioctl.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>

#define IOCTL_CMD _IO(0, 3)
int fd, fd2, led_flag = 0;

void btn_handler(int signum) { write(fd2, "0", 1); }

int main(void) {
  int retn;

  int flag = 0;
  signal(SIGIO, btn_handler);

  /* write에서 사용할 버퍼 */
  char buf[10] = {0};
  fd = open("/dev/gpiobtn", O_RDWR);
  fd2 = open("/dev/gpioled", O_RDWR);

  printf("fd = %d\n", fd);
  printf("fd2 = %d\n", fd2);
  if (fd < 0) {
    perror("/dev/gpiobtn error");
    exit(-1);
  } else
    printf("GPIOBTN has been detected...\n");

  if (fd2 < 0) {
    perror("/dev/gpioled error");
    exit(-1);
  } else
    printf("GPIOLED has been detected...\n");
  /* fd가 가르키는 파일에 buf에 있는 10바이트를 쓰라는 의미 */

  ioctl(fd, IOCTL_CMD, getpid());

  while (1) {
    sleep(1);
  }

  close(fd);
  return 0;
}
