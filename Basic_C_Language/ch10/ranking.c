#include <stdio.h>

void ranking(int *rank, const float *math);

int main(int argc, char *argv[]) {
  float math[5];
  int rank[5] = {0};

  printf("Enter five grades: ");
  for (int i = 0; i < 5; i++) {
    scanf("%f", &math[i]);
  }
  ranking(rank, math);
  for (int i = 0; i < 5; i++) {
    printf("Rank #%d : %d ", i + 1, rank[i]);
    printf("\n");
  }

  return 0;
}

void ranking(int *rank, const float *math) {
  int count;
  for (int i = 0; i < 5; i++) {
    count = 1;
    for (int j = 0; j < 5; j++) {
      if (i == j)
        continue;
      if (math[i] < math[j]) {
        count++;
      }
    }
    rank[i] = count;
  }
}
