#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

typedef void (*FPTR)(int, int);
void add(int n1, int n2);
void sub(int n1, int n2);
void mul(int n1, int n2);
void div(int n1, int n2);
void mod(int n1, int n2);

typedef struct CMD {
  char *cmd;
  FPTR fptr;
} CMD;

int main(int argc, char *argv[]) {
  char *input_cmd;
  int input_num1, input_num2, i;
  CMD command[] = {"add", add, "sub", sub, "mul", mul,
                   "div", div, "mod", mod, NULL,  NULL};

  while (1) {
    printf("Command, num1, num2: ");
    scanf("%s", input_cmd);
    if (strcmp(input_cmd, "NULL") == 0)
      break;
    scanf("%d%d", &input_num1, &input_num2);
    for (i = 0; command[i].cmd != NULL; i++) {
      if (!strcmp(input_cmd, command[i].cmd)) {
        command[i].fptr(input_num1, input_num2);
        break;
      }
    }
    if (command[i].cmd == NULL) {
      printf("Command not existed\n");
    }
  }

  return 0;
}

void add(int n1, int n2) {
  // this
  printf("%d + %d = %d\n", n1, n2, n1 + n2);
}
void sub(int n1, int n2) {
  // this
  printf("%d - %d = %d\n", n1, n2, n1 - n2);
}
void mul(int n1, int n2) {
  // this
  printf("%d * %d = %d\n", n1, n2, n1 * n2);
}
void div(int n1, int n2) {
  // this
  printf("%d / %d = %d\n", n1, n2, n1 / n2);
}

void mod(int n1, int n2) {
  // this
  printf("%d %% %d = %d\n", n1, n2, n1 % n2);
}
