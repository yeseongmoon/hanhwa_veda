#include <iostream>

int main(int argc, char *argv[]) {
  int size, input_num, last_num, arr_length;
  std::cin >> size >> input_num;
  arr_length = size, last_num = size * size;
  int arr[size][size];

  // filling order: down, right, up, and left
  while (1) {
    for (int i = 0; i < arr_length; i++) {
      arr[0][0] = last_num;
    }
  }

  return 0;
}
