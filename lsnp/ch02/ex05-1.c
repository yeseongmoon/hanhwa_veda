#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  struct utsname mysystem;
  char myhostname[256];
  if (gethostname(myhostname, 255) != 0) {
    perror("gethostname");
    exit(1);
  }

  if (uname(&mysystem) == -1) {
    perror("unname");
    exit(1);
  }

  printf("gethostname = %s\n", myhostname);
  printf("OS = %s\n", mysystem.sysname);
  printf("hostname = %s\n", mysystem.nodename);
  printf("release = %s\n", mysystem.release);
  printf("version = %s\n", mysystem.version);
  printf("hardware = %s\n", mysystem.machine);

  return 0;
}
