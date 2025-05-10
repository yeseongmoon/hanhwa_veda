#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char buffer[1024];
  int fd, n;
  if (argc != 2) {
    exit(1);
    fprintf(stderr, "Usage : ex01 device_filename\n");
  }
  if ((fd = open(argv[1], O_RDWR)) == -1) {
    perror("open");
    exit(1);
  }
  strcpy(buffer, "Hello, Terminal\n");
  n = strlen(buffer);
  write(fd, buffer, n);
  close(fd);
}
