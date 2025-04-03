#include <iostream>

void func(const char *) { std::cout << "[const char*]\n"; }

void func(int) { std::cout << "[int]\n"; }

int main(int argc, char *argv[]) {
  // int
  func(NULL);
  // char*
  func(nullptr);
  return 0;
}
