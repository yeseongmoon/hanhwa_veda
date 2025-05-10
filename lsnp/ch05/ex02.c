#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  switch (pid = fork()) {
  case -1:
    perror("fork");
    break;
  case 0:
    printf("CHILD PROCESS: %d\n", getpid());
    sleep(3);
    system("echo CHILD");
    system("ps -l");
    exit(0);
    break;
  default:
    printf("PARENT PROCESS: %d\n", getpid());
    printf("Return Value of fork: %d\n", pid);
    sleep(7);
    system("echo PARENT");
    system("ps -l");
    break;
  }
  return 0;
}
