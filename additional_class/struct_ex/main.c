#include <stdio.h>
#include <string.h>

struct Student {
  char name[20];
  int score;
};

int main(int argc, char *argv[]) {
  struct Student s = {"name", 30};
  strcpy(s.name, "Modify");
  s.score = 50;

  printf("%s : %d\n", s.name, s.score);

  return 0;
}
