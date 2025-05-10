#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SCORE {
  char name[20];
  int clang;
  int cpplang;
  float avg;
} SCORE;

int main(int argc, char *argv[]) {
  SCORE *score_array;
  char input_name[20];
  int clang_score, cpplang_score;
  LPARRAY tmp;
  int check = arrayCreate(&tmp);
  if (check != 0) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }

  for (int i = 0; i < 3; i++) {
    printf("Name clang score, cpplang score: ");
    score_array = malloc(sizeof(SCORE));
    scanf("%s%d%d", score_array->name, &score_array->clang,
          &score_array->cpplang);
    arrayAdd(tmp, score_array);
  }

  LPDATA *x;
  for (int i = 0; i < tmp->size; i++) {
    arrayGetAt(tmp, i, x);
    score_array = (SCORE *)&x;
    printf("%s %d %d\n", score_array->name, score_array->clang,
           score_array->cpplang);
  }

  return 0;
}
