#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  char date_time[10];

  char *input, *homedir, filename[80];
  FILE *fp;
  homedir = getenv("HOME");
  strcpy(filename, homedir);
  strftime(date_time, 1023, "/%Y%m%d", ltime);
  strcat(filename, date_time);

  if ((fp = fopen(filename, "w")) == NULL) {
    perror("fopen");
    exit(1);
  }

  while (1) {
    scanf("%s", input);
    if (*input == 'x')
      break;
    fwrite(input, 255, 255, fp);
  }
  fclose(fp);

  return 0;
}
