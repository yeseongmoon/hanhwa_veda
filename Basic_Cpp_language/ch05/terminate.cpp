#include <iostream>

int *ptr_int;

void myterminate() {
  delete[] ptr_int;
  ptr_int = nullptr;
  std::cout << "Memory deallocation successful." << std::endl;
  exit(-1);
}

int main(int argc, char *argv[]) {
  std::set_terminate(myterminate);
  int input_size;
  std::cout << "Enter an integer: ";
  std::cin >> input_size;

  ptr_int = new int[input_size]();
  for (int i = 0; i < 5; i++) {
    std::cout << ptr_int[i] << std::endl;
  }
  throw 1;

  return 0;
}
