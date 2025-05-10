#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

int main(void) {
  int i;
  time_t c_time;
  clock_t oldtime, newtime;
  struct tms oldtms, newtms;
  if ((oldtime = times(&oldtms)) == -1) {
    perror("old times");
    exit(1);
  }

  for (i = 1; i <= 99999999; i++)
    time(&c_time);
  if ((newtime = times(&newtms)) == -1) {
    perror("new times");
    exit(1);
  }

  int c_per_s = sysconf(_SC_CLK_TCK);

  printf("Real Time : %f clocks\n", (float)(newtime - oldtime) / c_per_s);
  printf("User mode Time : %f clocks\n",
         (float)(newtms.tms_utime - oldtms.tms_utime) / c_per_s);
  printf("System mode Time : %f clocks\n",
         (float)(newtms.tms_stime - oldtms.tms_stime) / c_per_s);
  return 0;
}
