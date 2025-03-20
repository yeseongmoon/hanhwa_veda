#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void sawp_ptr(char **ppa, char **ppb);
void print_ary(int (*)[4]);

int main(int argc, char *argv[]) {
  // pointer to pointer example
  /*int n1 = 100, n2 = 200;*/
  /*int *p = &n1;*/
  /*int **dp = &p;*/
  /**/
  /*printf("&n1: %p, p: %p, &p: %p, dp: %p\n", &n1, p, &p, dp);*/
  /*printf("n1 : %d, *p: %d, **dp: %d\n", n1, *p, **dp);*/
  /**/
  /*p++;*/
  /*dp++;*/
  /*printf("&n1: %p, p: %p, &p: %p, dp: %p\n", &n1, p, &p, dp);*/

  // swap addr
  /*char *pa = "success";*/
  /*char *pb = "failure";*/
  /**/
  /*printf("pa-> %s, pb-> %s\n", pa, pb);*/
  /*sawp_ptr(&pa, &pb);*/
  /*printf("pa-> %s, pb-> %s\n", pa, pb);*/

  // pointer to 2d array
  int ary[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  print_ary(ary);

  return 0;
}

void sawp_ptr(char **ppa, char **ppb) {
  char *pt;
  pt = *ppa;
  *ppa = *ppb;
  *ppb = pt;
}

void print_ary(int (*pa)[4]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%5d", pa[i][j]);
    }
    printf("\n");
  }
}
