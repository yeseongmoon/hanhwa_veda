#include <iostream>

int main(int argc, char *argv[]) {
  int *ptr_int_value = new int[5];

  for (int i = 0; i < 5; i++) {
    ptr_int_value[i] = 100 + i;
  }

  for (int i = 0; i < 5; i++) {
    std::cout << ptr_int_value[i] << std::endl;
  }

  delete[] ptr_int_value;
  return 0;
}
