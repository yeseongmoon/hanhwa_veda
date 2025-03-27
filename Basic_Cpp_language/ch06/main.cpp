#include "triangle.h"

int main(int argc, char *argv[]) {
  Triangle t;

  t.show();
  int area = t.get_area();

  std::cout << area << std::endl;

  Triangle tt(10, 25);
  tt.show();
  int area1 = tt.get_area();

  std::cout << area1 << std::endl;

  return 0;
}
