#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "shape.h"

class Triangle : public Shape {
  int base;
  int height;

public:
  Triangle();
  Triangle(int base, int height, std::string color);
  virtual ~Triangle();
  void show() override;
  int getArea() override;
  Triangle operator+(const Triangle &o) const;
  Triangle operator-(const Triangle &o) const;
  Triangle &operator+=(const Triangle &o);
  // void operator+=(const Triangle &o);
  friend bool equal(const Triangle &o1, const Triangle &o2);
  friend std::ostream &operator<<(std::ostream &os, const Triangle &t);
  friend std::istream &operator>>(std::istream &is, Triangle &t);
};

#endif
