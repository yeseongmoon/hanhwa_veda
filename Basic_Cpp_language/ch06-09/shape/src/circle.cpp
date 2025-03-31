#include "circle.h"

Circle::Circle() : radius(2) {}
Circle::Circle(int r, std::string color) : Shape(color) { this->radius = r; }
Circle::~Circle() {}
void Circle::show() {
  std::cout << "Circle Show\n";
  std::cout << "Radius: " << this->radius << std::endl;
  std::cout << "Color: " << this->color << std::endl;
}
int Circle::getArea() { return 2 * pi * radius; }
