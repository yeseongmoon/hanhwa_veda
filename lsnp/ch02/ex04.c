#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  struct passwd *userinfo;
  userinfo = getpwuid(getuid());
  printf("getpwuid() :\nname = %s, uid = %d, gid = %d, home directory = %s, "
         "shell = %s\n",
         userinfo->pw_name, userinfo->pw_uid, userinfo->pw_gid,
         userinfo->pw_dir, userinfo->pw_shell);
  userinfo = getpwnam(getlogin());
  printf("\ngetpwname() :\nname = %s, uid = %d, gid = %d, home directory = %s, "
         "shell = %s\n",
         userinfo->pw_name, userinfo->pw_uid, userinfo->pw_gid,
         userinfo->pw_dir, userinfo->pw_shell);
  return 0;
}
