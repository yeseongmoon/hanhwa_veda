#include "minishell.h"

void cmd_linux(char **arglist) {
  pid_t pid;
  int back_flag, redirect_flag, pos;
  back_flag = redirect_flag = FLAG_OFF;

  if (is_background(arglist)) {
    back_flag = FLAG_ON;
  }
  if ((pos = is_redirect(arglist)) > 0) {
    redirect_flag = FLAG_ON;
  }

  switch (pid = fork()) {
  case -1:
    perror("fork()");
    exit(1);
    break;
  case 0:
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (redirect_flag == FLAG_ON) {
      redirect(arglist, pos);
    }
    execvp(arglist[0], arglist);
    perror("execlp");
    exit(1);
    break;
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

int is_redirect(char **arglist) {
  for (int i = 0; arglist[i] != NULL; i++)
    if ((strcmp(arglist[i], ">") == 0) || (strcmp(arglist[i], "<") == 0) ||
        (strcmp(arglist[i], ">>") == 0))
      return i;
  return 0;
}
