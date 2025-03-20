#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void sawp_ptr(char **ppa, char **ppb);

int main(int argc, char *argv[]) {
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

  char *pa = "success";
  char *pb = "failure";

  printf("pa-> %s, pb-> %s\n", pa, pb);
  sawp_ptr(&pa, &pb);
  printf("pa-> %s, pb-> %s\n", pa, pb);

  return 0;
}

void sawp_ptr(char **ppa, char **ppb) {
  char *pt;
  pt = *ppa;
  *ppa = *ppb;
  *ppb = pt;
}
