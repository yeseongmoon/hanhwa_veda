#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd;
  char buffer[1024];
  if ((fd = open("dupest", O_RDONLY)) == -1) {
    perror("open");
    exit(1);
  }

  // close(1);
  // dup(fd);
  // close(fd);
  // write(1, buffer, strlen(buffer));
  // printf("This is dup() test file\n");

  close(0);
  dup(fd);
  while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    printf("%s\n", buffer);
  }
  close(fd);

  return 0;
}
