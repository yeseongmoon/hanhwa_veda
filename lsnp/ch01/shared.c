#include <stdio.h>

void shared_function(int num1, int num2) {
  printf("this is a shared library function = %d, %d\n", num1, num2);
}
