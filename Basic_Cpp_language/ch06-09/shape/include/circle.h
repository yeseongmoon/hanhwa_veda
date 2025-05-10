#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "shape.h"

const float pi = 3.14f;

class Circle : public Shape {
private:
  int radius;

public:
  Circle();
  Circle(int r, std::string color);
  virtual ~Circle();
  void show() override;
  int getArea() override;
};

#endif
