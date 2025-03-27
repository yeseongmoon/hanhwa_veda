#include "triangle.h"

Triangle::Triangle(int b, int h) {
  base = b;
  height = h;
}

Triangle::~Triangle() {
  base = 0;
  height = 0;
}

void Triangle::show() {
  std::cout << "base: " << base << std::endl;
  std::cout << "height: " << height << std::endl;
}

int Triangle::get_area() { return (base * height) / 2; }
