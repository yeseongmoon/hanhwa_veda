#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  struct passwd *pw;
  pw = getpwuid(getuid());
  printf("home directory = %s, login shell = %s\n", pw->pw_dir, pw->pw_shell);
  return 0;
}
