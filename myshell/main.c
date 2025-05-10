#include "minishell.h"

#define MAXLINE 255

int main(void) {
  char line[MAXLINE];
  char **arglist;

  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  struct sigaction act;

  act.sa_handler = child_handler;
  sigfillset(&act.sa_mask);
  act.sa_flags = SA_RESTART;
  sigaction(SIGCHLD, &act, NULL);

  fputs("myshell> ", stdout);
  while (fgets(line, MAXLINE, stdin)) {
    if (!strncmp(line, "exit", 4))
      exit(0);

    arglist = command_parse(line);
    if (arglist != NULL) {
      if (!is_builtin(arglist)) {
        cmd_linux(arglist);
      }
      command_freelist(arglist);
    }
    fputs("myshell> ", stdout);
  }
  return 0;
}
