#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t pid;
  pid = fork();

  switch (pid) {
  case -1:
    perror("fork()");
    exit(1);
    break;
  case 0:
    printf("CHILD Process\n");
    execlp("ls", "ls", "-l", (char *)0);
    perror("execlp");
    exit(0);
    break;
  default:
    wait(NULL);
    printf("child is dead\n");
    break;
  }

  return 0;
}
