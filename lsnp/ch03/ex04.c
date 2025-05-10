#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  int fd;
  struct stat statbuf;
  char *input;

  if ((fd = open("/etc/hosts", O_RDONLY)) == -1) {
    perror("open1");
    fprintf(stderr, "File Read Fail.....\n");
  } else {
    printf("File Read Success!! fd= %d\n", fd);

    fstat(fd, &statbuf);
    input = malloc(sizeof(char) * statbuf.st_size);
    read(fd, input, statbuf.st_size);
    close(fd);
  }

  if ((fd = open("myhosts", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    perror("open2");
    fprintf(stderr, "File Create Fail.....\n");
  } else {
    printf("File Creat Success!! fd= %d\n", fd);
    write(fd, input, statbuf.st_size);
    close(fd);
  }
  free(input);
  return 0;
}
