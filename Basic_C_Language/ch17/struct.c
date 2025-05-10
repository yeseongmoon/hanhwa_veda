#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

struct st {
  char name[22];
  int kor;
};

int main(int argc, char *argv[]) {
  /*struct st st1, st2;*/
  /*printf("%lu\n", sizeof(st1));*/
  /*printf("st1.name: %s st1.kor: %d\n", st1.name, st1.kor);*/
  /*st2 = st1;*/
  /*printf("st2.name: %s st2.kor: %d\n", st2.name, st2.kor);*/

  struct st st[5], *st_ptr = NULL;

  st_ptr = st;

  for (int i = 0; i < 5; i++) {
    printf("#%d. Name & score: ", i + 1);
    scanf("%s%d", (st_ptr + i)->name, &(st + i)->kor);
  }

  printf("Student list: \n");
  for (int i = 0; i < 5; i++) {
    printf("%s : %d\n", (st_ptr + i)->name, (st_ptr + i)->kor);
  }

  printf("\n");
  // remove the 3rd element from the struct array
  // memcpy(&st[2], &st[3], (5 - 2) * sizeof(st[0]));
  for (int i = 2; i < 4; i++) {
    *(st_ptr + i) = *(st_ptr + i + 1);
  }

  printf("Removed: \n");
  for (int i = 0; i < 4; i++) {
    printf("%s : %d\n", (st_ptr + i)->name, (st_ptr + i)->kor);
  }

  return 0;
}
