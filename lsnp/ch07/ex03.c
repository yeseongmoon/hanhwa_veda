#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXSIZE 4096

int main(int argc, char *argv[]) {
  int pd[2];
  pid_t pid;
  int n;
  char buf[MAXSIZE];
  if (pipe(pd) == -1) {
    perror("pipe");
    exit(1);
  }
  switch (pid = fork()) {
  case -1:
    perror("fork");
    exit(1);
    break;
  case 0:
    close(pd[0]);
    dup2(pd[1], 1);
    close(pd[1]);
    // strcpy(buf, "Hello, Parent!!");
    // write(pd[1], buf, strlen(buf));
    execlp("ps", "ps", "-l", NULL);
    perror("evexlp");
    exit(1);
    break;
  default:
    close(pd[1]);
    n = read(pd[0], buf, MAXSIZE);
    buf[n] = '\0';
    close(pd[0]);
    printf("PARENT: %s from CHILD\n", buf);
    if (waitpid(pid, NULL, 0) == -1) {
      perror("waitpid");
      exit(1);
    }
    break;
  }
  return 0;
}
