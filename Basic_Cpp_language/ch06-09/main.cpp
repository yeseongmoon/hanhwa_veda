#include "triangle.h"

int main(int argc, char *argv[]) {
  Triangle t;
  // t.show();
  // std::cout << "Area: " << t.get_area() << std::endl;

  Triangle s(10, 25);
  // s.show();
  // std::cout << "Area: " << s.get_area() << std::endl;

  // t = t + s;
  // t.show();
  //
  // t = t - s;
  // t.show();

  t += s;

  Triangle a, b;
  std::cout << std::boolalpha;
  std::cout << equal(a, b) << std::endl;

  // std::cout << "T --> " << t << std::endl;
  // std::cout << "S --> " << s << std::endl;
  // std::cout << "T --> " << t << "\nS --> " << s << std::endl;
  std::cout << "Base & Height: ";
  std::cin >> a >> b;
  std::cout << a << std::endl;
  std::cout << b << std::endl;

  return 0;
}
