#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>

int main(void) {
  int retn;
  int fd;

  int flag = 0;

  /* write에서 사용할 버퍼 */
  char buf[10] = {0};
  fd = open("/dev/gpioled", O_RDWR);

  printf("fd = %d\n", fd);
  if (fd < 0) {
    perror("/dev/gpioled error");
    exit(-1);
  } else
    printf("GPIOLED has been detected...\n");
  /* fd가 가르키는 파일에 buf에 있는 10바이트를 쓰라는 의미 */

  int choice;
  while (1) {
    printf("1. LED ON 2. LED OFF\n");
    printf("--> ");
    scanf("%d", &choice);
    if (choice == 1) {
      retn = write(fd, "1", 1);
    } else if (choice == 2) {
      retn = write(fd, "0", 1);
    }
  }

  close(fd);
  return 0;
}
