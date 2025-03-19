#include <stdio.h>

void static_function(int n);

// if the global variable is static, it means it cannot be accessed in other
// files.
static int hap = 0;

int main(int argc, char *argv[]) {
  // it is in the register. it can be loaded quicker. register > memory (spped
  // wise)
  register int i;
  for (int n = 1; n <= 10; n++) {
    static_function(n);
  }
  return 0;
}

void static_function(int n) {
  hap += n;
  printf("hap: %d\n", hap);
}
