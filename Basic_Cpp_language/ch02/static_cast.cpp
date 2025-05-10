#include <iostream>

int main(int argc, char *argv[]) {
  int num = 0x41;
  char *p1 = (char *)&num; // this can be done in C implicitly, but have
                           // undefined behavior == not recommended
  // char *p1 = static_cast<char *>(&num); <- not working
  std::cout << *p1 << std::endl;
  return 0;
}
