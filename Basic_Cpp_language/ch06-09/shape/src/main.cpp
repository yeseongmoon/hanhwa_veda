#include "circle.h"
#include "triangle.h"

int Shape::cntShape = 0;

int main(int argc, char *argv[]) {
  // Triangle t;
  // Shape *s = &t;
  // Shape &ss = t;
  //
  // s->show();
  // ss.show();
  // t.show();

  std::cout << "Before cntShape: " << Shape::getCntShape() << std::endl;
  Shape *s[3] = {new Circle(3, "yellow"), new Triangle(5, 7, "blue"),
                 new Triangle(8, 10, "green")};

  std::cout << "After cntShape: " << Shape::getCntShape() << std::endl;
  for (int i = 0; i < 3; i++) {
    s[i]->show();
    std::cout << s[i]->getArea() << std::endl;
  }

  for (int i = 0; i < 3; i++) {
    delete s[i];
  }

  // Triangle s(10, 25);
  // s.show();
  // std::cout << "Area: " << s.get_area() << std::endl;

  // t = t + s;
  // t.show();
  //
  // t = t - s;
  // t.show();

  // t += s;
  //
  // Triangle a, b;
  // std::cout << std::boolalpha;
  // std::cout << equal(a, b) << std::endl;
  //
  // std::cout << "T --> " << t << std::endl;
  // std::cout << "S --> " << s << std::endl;
  // std::cout << "T --> " << t << "\nS --> " << s << std::endl;
  // std::cout << "Base & Height: ";
  // std::cin >> a >> b;
  // std::cout << a << std::endl;
  // std::cout << b << std::endl;

  return 0;
}
