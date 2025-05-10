#include "minishell.h"

void child_handler(int signo) {
  pid_t pid;
  while (1) {
    pid = waitpid(0, NULL, WNOHANG);
    if (pid == 0) {
      break;
    } else if (pid == -1 && errno == ECHILD)
      break;
    else if (pid == -1) {
      perror("waitpid");
      exit(1);
    }
  }
}
