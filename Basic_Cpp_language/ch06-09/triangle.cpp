#include "triangle.h"

Triangle::Triangle() : base(10), height(20) {
  // std::cout << "Constructor\n";
}

Triangle::Triangle(int base, int height) {
  // std::cout << "Constructor\n";
  this->base = base;
  this->height = height;
}

Triangle::~Triangle() { this->base = 0, this->height = 0; }

// void Triangle::show() {
//   std::cout << "base: " << base << std::endl;
//   std::cout << "height: " << height << std::endl;
// }

int Triangle::get_area() { return (base * height) / 2; }

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
