#include <array>
#include <iostream>

int main(int argc, char *argv[]) {
  try {
    std::array<int, 5> myArray;
    myArray = {1, 2, 3, 4, 5};

    std::cout << "Print the array: ";
    for (auto &element : myArray) {
      std::cout << element << " ";
    }
    std::cout << std::endl;

    std::cout << "Size of the array: " << myArray.size() << std::endl;
    std::cout << "First element of the array: " << myArray[0] << std::endl;
    // NOTE: : catch cannot detect this as an error
    myArray[10] = 10;
    // this is catchable
    myArray.at(10) = 10;

    std::cout << "Modified myArray: ";
    for (int i = 0; i < 5; i++) {
      std::cout << myArray[i] << " ";
    }
    std::cout << std::endl;
  } catch (...) {
    std::cout << "exception occurred!\n";
  }

  return 0;
}
