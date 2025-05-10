#include "minishell.h"

void redirect(char **arglist, int pos) {
  if (strcmp(arglist[pos], ">") == 0) {
    int fd;
    if ((fd = open(arglist[pos + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) ==
        -1) {
      perror("open");
      close(fd);
      exit(1);
    }
    dup2(fd, 1); // stdout
    close(fd);
    arglist[pos] = NULL;
  } else if (strcmp(arglist[pos], ">>") == 0) {
    int fd;
    if ((fd = open(arglist[pos + 1], O_WRONLY | O_CREAT | O_APPEND, 0644)) ==
        -1) {
      perror("open");
      close(fd);
      exit(1);
    }
    dup2(fd, 1);
    close(fd);
    arglist[pos] = NULL;

  } else if (strcmp(arglist[pos], "<") == 0) {
    int fd;
    if ((fd = open(arglist[pos + 1], O_RDONLY)) == -1) {
      perror("open");
      close(fd);
      exit(1);
    }
    dup2(fd, 0);
    close(fd);

    arglist[pos] = NULL;
  }
}
