#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("%d\n", getpid());
  printf("%d\n", getppid());
  return 0;
}
