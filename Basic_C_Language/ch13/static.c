#include <stdio.h>

void static_function(int n);

int main(int argc, char *argv[]) {
  for (int n = 1; n <= 10; n++) {
    static_function(n);
  }
  return 0;
}

void static_function(int n) {
  static int hap = 0;
  hap += n;
  printf("hap: %d\n", hap);
}
