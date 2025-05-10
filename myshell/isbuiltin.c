// is_builtin() : if the command is a built-in command, use the built-in
// command; otherwise, use a custom command.
// e.g. if command is "cd" -> use chdir (~/)

#include "minishell.h"

BIC bt_array[] = {
    "cd", cd_function, "pwd", pwd_function, NULL, NULL,
};

int is_builtin(char **arglist) {
  for (int i = 0; bt_array[i].cmd != NULL; i++) {
    if (strcmp(arglist[0], bt_array[i].cmd) == 0) {
      bt_array[i].fptr(arglist);
      return 1;
    }
  }
  return 0;
}

void cd_function(char **arglist) {
  if (arglist[1] == NULL) {
    chdir(getenv("HOME"));
  } else {
    if (chdir(arglist[1]) == -1)
      perror("chdir");
  }
}

void pwd_function(char **arglist) {
  char cwd[1024];
  getcwd(cwd, 1024);
  printf("current working diretory : %s\n", cwd);
}
