#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  sigset_t set1, set2;
  sigfillset(&set1);
  sigemptyset(&set2);
  sigaddset(&set2, SIGINT);
  sigprocmask(SIG_BLOCK, &set1, NULL);
  printf("signal block start\n");
  sleep(5);

  sigprocmask(SIG_UNBLOCK, &set2, NULL);
  while (1) {
    printf("hello signal\n");
    sleep(2);
  }
  return 0;
}
