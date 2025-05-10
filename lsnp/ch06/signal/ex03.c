#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  sigset_t sigset;
  sigset_t pendingset;
  int i = 0;
  sigfillset(&sigset);
  sigprocmask(SIG_SETMASK, &sigset, NULL);
  printf("waiting for signal ... (10 secs) \n");
  for (i = 0; i < 10; i++) {
    printf("count: %d\n", i + 1);
    sleep(1);
  }

  if (sigpending(&pendingset) == 0) {
    printf("I got : \n");
    if (sigismember(&pendingset, SIGINT)) {
      printf("SIGINT\n");
    } else if (sigismember(&pendingset, SIGQUIT)) {
      printf("SIGQUIT\n");
    } else if (sigismember(&pendingset, SIGUSR1)) {
      printf("SIGUSR1\n");
    } else if (sigismember(&pendingset, SIGUSR2)) {
      printf("SIGUSR2\n");
    }
  }

  return 0;
}
