#include "shape.h"

Shape::Shape() : Shape("white") { // std::cout << "Shape's Constructor\n";
  ++cntShape;
}
Shape::Shape(std::string color) {
  this->color = color;
  ++cntShape;
  // std::cout << "Shape's Constructor with an argument\n";
}
Shape::~Shape() { // std::cout << "Shape's Destructor\n";
}

int Shape::getCntShape() { return cntShape; }

std::string Shape::getColor() { return this->color; }
void Shape::setColor(std::string color) { this->color = color; }
void Shape::show() {
  std::cout << "Shape Show\n";
  std::cout << "color: " << this->color << std::endl;
}
