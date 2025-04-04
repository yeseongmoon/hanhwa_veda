#include <iostream>
class Shape {
public:
  void show() { std::cout << "shape\n"; }
};
class Rect : public Shape {
public:
  void show() { std::cout << "Rect\n"; }
};

int main(int argc, char *argv[]) {
  Shape s;
  Rect r;

  Shape &ss = static_cast<Shape &>(r);
  ss.show();

  Shape *sss = new Shape;
  Rect *rr = static_cast<Rect *>(sss);
  rr->show();

  Rect &rrr = static_cast<Rect &>(s);
  rrr.show();

  return 0;
}
