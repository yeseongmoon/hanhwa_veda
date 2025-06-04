#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <termio.h>
#include <unistd.h>

int main(void) {
  int retn;
  int fd;

  int flag = 0;

  /* write에서 사용할 버퍼 */
  char buf[10] = {0};
  fd = open("/dev/gpiospk", O_RDWR);

  printf("fd = %d\n", fd);
  if (fd < 0) {
    perror("/dev/gpiospk error");
    exit(-1);
  } else
    printf("GPIOSPK has been detected...\n");
  /* fd가 가르키는 파일에 buf에 있는 10바이트를 쓰라는 의미 */

  int choice;
  pid_t child_pid;
  while (1) {
    printf("1. SPK ON 2. SPK OFF\n");
    printf("--> ");
    scanf("%d", &choice);
    if (choice == 1) {
      child_pid = fork();
      if (child_pid == 0) {
        retn = write(fd, "1", 1);
        exit(0);
      }
    } else if (choice == 2) {
      if (child_pid > 0) {
        retn = write(fd, "0", 1);
        kill(child_pid, SIGKILL);
        waitpid(child_pid, NULL, 0);
      }
    }
  }

  close(fd);
  return 0;
}
