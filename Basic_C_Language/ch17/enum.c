#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

typedef enum os {
  LINUX = 1,
  WINDOW,
  MACOS,
} os;

int main(int argc, char *argv[]) {
  os operating_system;

  scanf("%d", &operating_system);
  switch (operating_system) {
  case LINUX:
    printf("LINUX OS : %d\n", operating_system);
    break;
  case WINDOW:
    printf("WINDOW OS : %d\n", operating_system);
    break;
  case MACOS:
    printf("MACOS : %d\n", operating_system);
    break;
  }
  return 0;
}
