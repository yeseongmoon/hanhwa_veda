#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  sigset_t set;
  sigfillset(&set);
  sigdelset(&set, SIGINT);
  sigprocmask(SIG_SETMASK, &set, NULL);

  while (1) {
    printf("while loop\n");
    sleep(1);
  }

  return 0;
}
