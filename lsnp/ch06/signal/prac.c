#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int count1 = 0, count2 = 0;

void user1_handler() { count1++; }
void user2_handler() { count2++; }
void sig_handler() {
  printf("\nuser1 = %d, user2 = %d\n", count1, count2);
  exit(0);
}

int main(int argc, char *argv[]) {
  sigset_t sigset;

  signal(SIGINT, sig_handler);
  signal(SIGUSR1, user1_handler);
  signal(SIGUSR2, user2_handler);

  sigfillset(&sigset);

  sigdelset(&sigset, SIGUSR1);
  sigdelset(&sigset, SIGUSR2);
  sigdelset(&sigset, SIGINT);

  sigprocmask(SIG_SETMASK, &sigset, NULL);

  while (1)
    ;

  return 0;
}
