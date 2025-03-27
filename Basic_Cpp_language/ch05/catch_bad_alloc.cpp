#include <iostream>
#include <ostream>

int main(int argc, char *argv[]) {
  try {
    int *ptr = new int;

  } catch (const std::bad_alloc) {
    std::cout << "Memory allocation failed." << std::endl;
  }
  return 0;
}
