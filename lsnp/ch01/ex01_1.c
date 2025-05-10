#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]) {
  time_t *cur_time = (time_t *)malloc(sizeof(time_t));
  time(cur_time);
  printf("Current Time = %d\n", (int)*cur_time);
  char *cur_string;
  cur_string = ctime(cur_time);
  printf("Current Time = %s\n", cur_string);
  return 0;
}
