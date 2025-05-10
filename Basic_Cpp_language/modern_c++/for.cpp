#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  int arr[] = {0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9};
  for (auto &a : arr) {
    std::cout << a << " ";
  }
  std::cout << std::endl;

  std::string input;
  std::vector<std::string> v;
  int a{5};
  char c{'a'};
  int b(5);
  std::string name{"John"};

  while (1) {
    std::cout << "Enter a string: ";
    std::cin >> input;
    if (input == "end")
      break;
    v.push_back(input);
  }

  for (auto it : v) {
    std::cout << it << std::endl;
  }

  return 0;
}
