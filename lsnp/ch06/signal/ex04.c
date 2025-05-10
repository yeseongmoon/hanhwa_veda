#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  sigset_t sigset;

  sigfillset(&sigset);
  sigprocmask(SIG_BLOCK, &sigset, NULL);

  sigfillset(&sigset);
  sigdelset(&sigset, SIGINT);
  sigsuspend(&sigset);

  return 0;
}
