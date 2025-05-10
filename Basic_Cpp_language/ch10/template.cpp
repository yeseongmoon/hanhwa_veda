#include <iostream>

class Circle {
  int radius;

public:
  Circle(int radius = 1) { this->radius = radius; }
  int getRadius() { return radius; }
};

// NOTE: : template is a very useful tool, but it is very hard to debug
template <class T> void mySwap(T &a, T &b) {
  T tmp;
  tmp = a;
  a = b;
  b = tmp;
}

int main(int argc, char *argv[]) {
  int a = 4, b = 5;
  mySwap(a, b);
  std::cout << "a=" << a << ", b=" << b << std::endl;
  double c = 0.3, d = 12.5;
  mySwap(c, d);
  std::cout << "c=" << c << ", d=" << d << std::endl;

  Circle donut(5), pizza(20);
  mySwap(donut, pizza);
  std::cout << "Radius of donut=" << donut.getRadius()
            << ", Radius of pizza=" << pizza.getRadius() << std::endl;

  std::string s1 = "ABC", s2 = "DEF";
  mySwap(s1, s2);
  std::cout << "s1=" << s1 << ", s2=" << s2 << std::endl;
  return 0;
}
