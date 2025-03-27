#include <iostream>
#include <limits.h>

int main(int argc, char *argv[]) {
  unsigned int input_num1, input_num2;
  std::cout << "Please enter an integer: ";
  std::cin >> input_num1;

  std::cout << "Please enter an integer that you would like to multiply to: ";
  std::cin >> input_num2;

  unsigned int result = input_num1 * input_num2;
  try {
    if (result > INT_MAX)
      throw INT_MAX;
  } catch (int max) {
    std::cout << "Result is bigger than the INT_MAX number." << std::endl;
  }
  return 0;
}
