#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]) {
  time_t *cur_time;
  time(cur_time);
  printf("Current Time = %d\n", (int)*cur_time);
  return 0;
}
