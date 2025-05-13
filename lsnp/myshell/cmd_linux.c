#include "minishell.h"

void cmd_linux(char **arglist) {
  pid_t pid;
  int back_flag, pos;

  if (is_background(arglist)) {
    back_flag = FLAG_ON;
  }

  switch (pid = fork()) {
  case -1:
    perror("fork()");
    exit(1);
    break;
  case 0:
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    redirect(arglist);
    if ((pos = is_pipe(arglist)) > 0) {
      custom_pipe(arglist, pos);
    } else {
      execvp(arglist[0], arglist);
      perror("execlp");
      exit(1);
      break;
    }
  default:
    if (back_flag == FLAG_OFF) {
      waitpid(pid, NULL, 0);
    }
    break;
  }
}

int is_background(char **arglist) {
  int i;
  for (i = 0; arglist[i] != NULL; i++)
    ;
  if (strcmp(arglist[i - 1], "&") == 0) {
    arglist[i - 1] = NULL;
    return 1;
  }
  return 0;
}

int is_pipe(char **arglist) {
  for (int i = 0; arglist[i] != NULL; i++) {
    if (strcmp(arglist[i], "|") == 0)
      return i;
  }
  return 0;
}
