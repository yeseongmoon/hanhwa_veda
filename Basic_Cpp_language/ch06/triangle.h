#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <iostream>

class Triangle {
  int base;
  int height;

public:
  Triangle(int b = 10, int h = 20);
  ~Triangle();
  void show();
  int get_area();
};

#endif
