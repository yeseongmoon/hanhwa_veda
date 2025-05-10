#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

static int alarm_flag = 0;

void alarm_handler(int sig) { alarm_flag = 1; }

void interval_handler(int sig) {
  printf("<interval handler> called : %ld\n", time(NULL));
}

int main(int argc, char *argv[]) {
  struct sigaction act;
  struct itimerval itimer;
  act.sa_handler = interval_handler;
  sigfillset(&act.sa_mask);
  act.sa_flags = SA_RESTART;
  sigaction(SIGALRM, &act, NULL);
  printf("<main> Current Time : %ld\n", time(NULL));
  memset(&itimer, 0, sizeof(itimer));
  itimer.it_value.tv_sec = 5;
  itimer.it_interval.tv_sec = 2;
  setitimer(ITIMER_REAL, &itimer, NULL);

  while (1)
    pause();

  return 0;
}
