#include <iostream>

float square(float a) { return a * a; }

double square(double a) { return a * a; }

int main(int argc, char *argv[]) {
  std::cout << square(3.0);
  // std::cout << square(3);

  return 0;
}
