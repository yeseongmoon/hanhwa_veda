#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termio.h>
#include <termios.h>
#include <unistd.h>

#define CR '\012'

int main(int argc, char *argv[]) {
  struct termio tbuf, oldtbuf;
  char ch[18];
  int i = 0;
  if (ioctl(0, TCGETA, &tbuf) == -1) {
    perror("ioctl");
    exit(1);
  }

  oldtbuf = tbuf;
  tbuf.c_lflag &= ~ICANON;
  tbuf.c_lflag &= ~ECHO;
  tbuf.c_cc[VMIN] = 1;
  tbuf.c_cc[VTIME] = 0;
  if (ioctl(0, TCSETAF, &tbuf) == -1) {
    perror("ioctl");
    exit(1);
  }

  while (i < 18) {
    ch[i] = getchar();
    if (ch[i] == CR)
      break;
    printf("*");
    i++;
  }
  printf("\n");
  ch[i] = '\0';
  printf("%s\n", ch);
  if (ioctl(0, TCSETAF, &oldtbuf) == -1) {
    perror("ioctl");
    exit(1);
  }

  return 0;
}
