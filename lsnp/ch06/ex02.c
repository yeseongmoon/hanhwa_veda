#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int signo) {
  write(1, "Control_c\n", 10);
  printf("Signal=%d\n", signo);
}

int main(int argc, char *argv[]) {
  signal(SIGINT, handler);

  for (int i = 0; i < 5; i++) {
    printf("handler\n");
    sleep(1);
  }

  signal(SIGINT, SIG_DFL);

  while (1) {
    printf("while loop\n");
    sleep(1);
  }

  return 0;
}
