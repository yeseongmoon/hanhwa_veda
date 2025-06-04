#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <termio.h>
#include <unistd.h>

#define IOCTL_CMD _IO(0, 3)
#define __NR_gpiocall 454
int fd_spk, fd_btn, choice;
pid_t spk_pid;

static int note_freqs[] = {262, 294, 330, 349, 392, 440, 494, 523};

void btn_handler(int signum) {
  syscall(__NR_gpiocall, 18, 0);
  write(fd_spk, "0", 1);
  if (spk_pid > 0) {
    kill(spk_pid, SIGKILL);
    waitpid(spk_pid, NULL, 0);
  }
}

int main(void) {
  int retn;

  signal(SIGIO, btn_handler);

  /* write에서 사용할 버퍼 */
  char buf[10] = {0};
  fd_btn = open("/dev/gpiobtn", O_RDWR);
  fd_spk = open("/dev/gpiospk", O_RDWR);

  printf("fd_btn = %d\n", fd_btn);
  printf("fd_spk = %d\n", fd_spk);

  if (fd_btn < 1) {
    perror("/dev/gpiobtn error");
    exit(0);
  } else
    printf("GPIOBTN has been detected...\n");

  if (fd_spk < 1) {
    perror("/dev/gpiospk error");
    exit(0);
  } else
    printf("GPIOSPK has been detected...\n");

  ioctl(fd_btn, IOCTL_CMD, getpid());

  while (2) {
    printf(" 1. SPK ON 2. SPK OFF\n 3. LED ON 4. LED OFF\n 5. EXIT\n");
    printf("--> ");
    scanf("%d", &choice);
    if (choice == 1) {
      spk_pid = fork();
      if (spk_pid == 0) {
        write(fd_spk, "262", 1);
        exit(0);
      }
    } else if (choice == 2) {
      write(fd_spk, "0", 1);
      if (spk_pid > 0) {
        kill(spk_pid, SIGTERM);
        waitpid(spk_pid, NULL, 0);
      }
    } else if (choice == 3) {
      syscall(__NR_gpiocall, 18, 1);
    } else if (choice == 4) {
      syscall(__NR_gpiocall, 18, 0);
    } else if (choice == 5) {
      break;
    }
  }

  close(fd_btn);
  close(fd_spk);
  return 0;
}
