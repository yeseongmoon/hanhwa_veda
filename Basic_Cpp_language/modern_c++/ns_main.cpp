#include "ns.hpp"

#include <stdlib.h>
void test() { std::cout << "test function not in namespace\n"; }

int main(int argc, char *argv[]) {
  test();
  NS::test();
  NS::Space rocket;
  rocket.fly();
  return 0;
}
