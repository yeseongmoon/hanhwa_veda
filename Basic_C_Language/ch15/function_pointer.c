#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void add(int, int);
void sub(int, int);
void mult(int n1, int n2);
void div(int n1, int n2);

int main(int argc, char *argv[]) {
  int n1, n2;
  // array pointer to function
  void (*fp[4])(int, int) = {add, sub, mult, div};

  int op;
  printf("1. + \n2. - \n3. x \n4. / \n");
  printf("--> ");
  scanf("%d", &op);
  getchar();
  scanf("%d%d", &n1, &n2);
  getchar();
  fp[op - 1](n1, n2);

  /*switch (op) {*/
  /*case '+':*/
  /*  fp[0](n1, n2);*/
  /*  break;*/
  /*case '-':*/
  /*  fp[1](n1, n2);*/
  /*  break;*/
  /*case 'x':*/
  /*  fp[2](n1, n2);*/
  /*  break;*/
  /*case '/':*/
  /*  fp[3](n1, n2);*/
  /*  break;*/
  /*default:*/
  /*  printf("Not a valid input\n");*/
  /*  break;*/
  /*}*/
  return 0;
}

void add(int n1, int n2) { printf("add: %d\n", n1 + n2); }
void sub(int n1, int n2) { printf("sub: %d\n", n1 - n2); }
void mult(int n1, int n2) { printf("multi: %d\n", n1 * n2); }
void div(int n1, int n2) { printf("div: %d\n", n1 / n2); }
