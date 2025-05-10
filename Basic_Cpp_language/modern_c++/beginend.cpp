#include <iostream>

int main(int argc, char *argv[]) {
  int arr[5] = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << "\n";

  for (auto i = std::begin(arr); i != std::end(arr); i++) {
    std::cout << *i << " ";
  }
  std::cout << "\n";

  return 0;
}
