#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void swap_func(void *vp1, void *vp2, int type);

int main(int argc, char *argv[]) {
  int n1 = 123, n2 = 456;
  double d1 = 763.4567, d2 = 567.9234;
  // when using void pointer, you have to know how big the variable's memory
  // type is

  printf("given integers : %d %d\n", n1, n2);
  swap_func(&n1, &n2, 1);
  printf("swaped : %d %d\n\n", n1, n2);

  printf("given doubles : %.4lf %.4lf\n", d1, d2);
  swap_func(&d1, &d2, 2);
  printf("swaped : %.4lf %.4lf\n", d1, d2);
  /*vp = &n;*/
  /*printf("%d\n", *(int *)vp);*/
  /**/
  /*vp = &d;*/
  /*printf("%lf\n", *(double *)vp);*/

  return 0;
}

void swap_func(void *vp1, void *vp2, int type) {
  if (type == 1) {
    int temp;
    temp = *(int *)vp1;
    *(int *)vp1 = *(int *)vp2;
    *(int *)vp2 = temp;
  }
  if (type == 2) {
    double temp;
    temp = *(double *)vp1;
    *(double *)vp1 = *(double *)vp2;
    *(double *)vp2 = temp;
  }
}
