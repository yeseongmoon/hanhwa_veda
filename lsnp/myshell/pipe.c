#include "minishell.h"

void custom_pipe(char **arglist, int pos) {
  int pd[2], n;
  pipe(pd);
  switch (fork()) {
  case -1:
    perror("fork");
    exit(1);
    break;
  case 0:
    arglist[pos] = NULL;
    close(pd[0]);
    dup2(pd[1], 1);
    close(pd[1]);
    execvp(arglist[0], arglist);
    perror("execvp_c");
    exit(1);
    break;
  default:
    close(pd[1]);
    dup2(pd[0], 0);
    close(pd[0]);
    execvp(arglist[pos + 1], &arglist[pos + 1]);
    perror("execvp_p");
    exit(1);
  }
}
