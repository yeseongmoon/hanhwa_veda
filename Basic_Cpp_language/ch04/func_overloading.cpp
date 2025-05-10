#include <iostream>

int sum(int a, int b, int c) { return a + b + c; }

double sum(double a, double b) { return a + b; }

int sum(int a, int b) { return a + b; }

int main(int argc, char *argv[]) {
  std::cout << "int sun(int, int): " << sum(1, 2) << std::endl;
  std::cout << "int sum(int,int,int): " << sum(1, 2, 3) << std::endl;
  std::cout << "double sum(double, double): " << sum(1.5, 2.5) << std::endl;
  return 0;
}
