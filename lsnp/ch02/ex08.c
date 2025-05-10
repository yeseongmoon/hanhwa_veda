#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

void openfile_test(void);

int main(int argc, char *argv[]) {
  struct rlimit mylimit;

  getrlimit(RLIMIT_NPROC, &mylimit);
  printf("Current Number of Process : softlimit=%ld, hardlimit=%ld\n",
         mylimit.rlim_cur, mylimit.rlim_max);

  getrlimit(RLIMIT_NOFILE, &mylimit);
  printf("Current Number of File : softlimit=%ld, hardlimit=%ld\n",
         mylimit.rlim_cur, mylimit.rlim_max);

  mylimit.rlim_cur = 5;
  setrlimit(RLIMIT_NOFILE, &mylimit);
  openfile_test();
  return 0;
}

void openfile_test() {
  char *filename[6] = {"test1", "test2", "test3", "test4", "test5", "test6"};
  FILE *fp;
  int i;
  for (int i = 0; i < 6; i++) {
    if ((fp = fopen(filename[i], "w")) == NULL) {
      perror(filename[i]);
      exit(1);
    }
  }
}
