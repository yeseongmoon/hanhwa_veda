#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  time_t cur_time;
  if (time(&cur_time) == -1) {
    perror("time");
    exit(1);
  }

  struct tm *ltime;

  ltime = localtime(&cur_time);

  printf("%d-%d-%d\n", ltime->tm_year + 1900, ltime->tm_mon + 1,
         ltime->tm_mday);

  return 0;
}
