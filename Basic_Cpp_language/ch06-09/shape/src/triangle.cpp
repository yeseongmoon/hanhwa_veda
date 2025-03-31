#include "triangle.h"

Triangle::Triangle() : base(10), height(20) {
  // std::cout << "Triangle's Constructor\n";
}

// NOTE: : You can do either Shape(color) or this->color = color.
Triangle::Triangle(int base, int height, std::string color) : Shape(color) {
  // std::cout << "Triangle's Constructor with arguments\n";
  //  NOTE: : if color is private member, child class cannot access the data.
  //          if it is private member, then it can only be initialized with
  //          Shape(color)

  // this->color = color;
  this->base = base;
  this->height = height;
}

Triangle::~Triangle() { // std::cout << "Triangle's Destructor\n";
}

void Triangle::show() {
  std::cout << "Triangle Show\n";
  std::cout << "base: " << base << std::endl;
  std::cout << "height: " << height << std::endl;
  std::cout << "color: " << color << std::endl;
}

int Triangle::getArea() { return (base * height) / 2; }

Triangle Triangle::operator+(const Triangle &o) const {
  Triangle tmp;
  tmp.base = this->base + o.base;
  tmp.height = this->height + o.height;
  return tmp;
}

Triangle Triangle::operator-(const Triangle &o) const {
  Triangle tmp;
  tmp.base = this->base - o.base;
  tmp.height = this->height - o.height;
  return tmp;
}

// NOTE: : instaed of this method, it's better to return the reference value
// like below
// void Triangle::operator+=(const Triangle &o) {
//   this->base = this->base + o.base;
//   this->height = this->height + o.height;
// }

Triangle &Triangle::operator+=(const Triangle &o) {
  // NOTE: : this can be done if + operator is implemented.
  //*this = *this + o;
  this->base = this->base + o.base;
  this->height = this->height + o.height;

  return *this;
}

bool equal(const Triangle &o1, const Triangle &o2) {
  if (o1.base == o2.base && o1.height == o2.height) {
    return true;
  }
  return false;
}

std::ostream &operator<<(std::ostream &os, const Triangle &t) {
  os << "Base: " << t.base << " Height: " << t.height;
  return os;
}

std::istream &operator>>(std::istream &is, Triangle &t) {
  is >> t.base >> t.height;
  return is;
}
