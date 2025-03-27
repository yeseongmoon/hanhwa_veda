#include <iostream>

// NOTE: : default arguments can be done only in forward declaraion
void f(char c = ' ', int size = 1);

int main(int argc, char *argv[]) {
  f();
  f('%');
  f('@', 5);

  return 0;
}

void f(char c, int size) {

  while (size--) {
    for (int i = 0; i < 10; i++) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
}
