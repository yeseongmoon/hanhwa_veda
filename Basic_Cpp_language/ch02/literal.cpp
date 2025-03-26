#include <iostream>

int main(int argc, char *argv[]) {
  std::string string_value("Hello");
  /*std::cout << string_value << std::endl;*/
  string_value = "World";
  /*std::cout << string_value << std::endl;*/

  std::string input_string;
  std::cout << "Enter a word: ";
  std::cin >> input_string;

  if (input_string == string_value)
    std::cout << "Same" << std::endl;
  else
    std::cout << "Not the same" << std::endl;

  return 0;
}
