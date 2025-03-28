#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <iostream>

class Triangle {
  int base;
  int height;

public:
  Triangle();
  Triangle(int base, int height);
  ~Triangle();
  // void show();
  int get_area();
  Triangle operator+(const Triangle &o) const;
  Triangle operator-(const Triangle &o) const;
  Triangle &operator+=(const Triangle &o);
  // void operator+=(const Triangle &o);
  friend bool equal(const Triangle &o1, const Triangle &o2);
  friend std::ostream &operator<<(std::ostream &os, const Triangle &t);
  friend std::istream &operator>>(std::istream &is, Triangle &t);
};

#endif
