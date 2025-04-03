#include <iostream>

int main(int argc, char *argv[]) {
  auto add = [](int n1, int n2) -> int { return n1 + n2; };
  std::cout << add(10, 20) << std::endl;
  return 0;
}
