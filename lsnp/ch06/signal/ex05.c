#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

static int alarm_flag = 0;

void alarm_handler(int sig) { alarm_flag = 1; }

int main(int argc, char *argv[]) {
  struct sigaction act;
  act.sa_handler = alarm_handler;
  sigfillset(&act.sa_mask);
  act.sa_flags = SA_RESTART;
  sigaction(SIGALRM, &act, NULL);
  alarm(5);
  pause();
  if (alarm_flag)
    printf("ALARM\n");

  return 0;
}
