#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char *argv[]) {
  /*int n1 = 10, n2 = 20, n3 = 30;*/
  /**/
  /*int *ptr_arr[3] = {&n1, &n2, &n3};*/
  /*int sum = 0;*/
  /*for (int i = 0; i < 3; i++) {*/
  /*  sum += *ptr_arr[i];*/
  /*}*/
  /*printf("Sum: %d\n", sum);*/

  char *strings[3] = {"hi", "hello", "bye"};

  for (int i = 0; i < 3; i++) {
    printf("%s\n", strings[i]);
  }

  return 0;
}
