#include "sk_ioctl.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>

#define IOCTL_CMD _IO(0, 3)
int fd_led, fd_btn, fd_cds, sig = 0;

void btn_handler(int signum) {
  printf("Button Handler!\n");
  write(fd_led, "0", 1);
  sig = 1;
}

int main(void) {
  int retn;

  signal(SIGIO, btn_handler);

  /* write에서 사용할 버퍼 */
  char buf[10] = {0};
  fd_btn = open("/dev/gpiobtn", O_RDWR);
  fd_led = open("/dev/gpioled", O_RDWR);
  fd_cds = open("/dev/gpiocds", O_RDWR);

  printf("fd_btn = %d\n", fd_btn);
  printf("fd_led = %d\n", fd_led);
  printf("fd_cds = %d\n", fd_cds);

  if (fd_btn < 0) {
    perror("/dev/gpiobtn error");
    exit(-1);
  } else
    printf("GPIOBTN has been detected...\n");

  if (fd_led < 0) {
    perror("/dev/gpioled error");
    exit(-1);
  } else
    printf("GPIOLED has been detected...\n");

  if (fd_cds < 0) {
    perror("/dev/gpiocds error");
    exit(-1);
  } else
    printf("GPIOCDS has been detected...\n");
  /* fd가 가르키는 파일에 buf에 있는 10바이트를 쓰라는 의미 */

  ioctl(fd_btn, IOCTL_CMD, getpid());

  while (1) {
    if (sig == 1)
      break;
    lseek(fd_cds, 0, SEEK_SET);
    read(fd_cds, buf, 10);
    if (strcmp(buf, "1") == 0) {
      write(fd_led, "1", 1);
    } else if (strcmp(buf, "0") == 0) {
      write(fd_led, "0", 1);
    }

    sleep(1);
  }

  close(fd_btn);
  close(fd_cds);
  close(fd_led);
  return 0;
}
