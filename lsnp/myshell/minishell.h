#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char **command_parse(char *);
void command_freelist(char **);
int is_builtin(char **);
void cmd_linux(char **);

typedef struct builtin_cmd {
  char *cmd;
  void (*fptr)(char **);
} BIC;

enum flag { FLAG_OFF, FLAG_ON };

void pwd_function(char **);
void cd_function(char **);
int is_background(char **);
int is_redirect(char **);
void child_handler(int);
void redirect(char **, int);
