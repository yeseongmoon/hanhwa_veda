#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  int status;
  switch (pid = fork()) {
  case -1:
    perror("fork");
    break;
  case 0:
    printf("CHILD PROCESS: %d\n", getpid());
    sleep(1000);
    system("echo CHILD");
    system("ps -l");
    exit(0);
    break;
  default:
    printf("PARENT PROCESS: %d\n", getpid());
    printf("Return Value of fork: %d\n", pid);
    wait(&status);
    if (WIFEXITED(status)) {
      printf("dead by exit()\n");
    } else if (WIFSIGNALED(status)) {
      printf("dead by signal\n");
    }
    system("echo PARENT");
    system("ps -l");
    break;
  }
  return 0;
}
