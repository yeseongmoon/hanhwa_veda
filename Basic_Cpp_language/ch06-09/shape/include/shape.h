#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <iostream>

class Shape {
protected:
  std::string color;
  static int cntShape;

public:
  Shape();
  Shape(std::string color);
  // NOTE: : If there's a virtual class function, you need to make the
  //         destructor to be virtual as well (for child too)
  virtual ~Shape();
  static int getCntShape();
  std::string getColor();
  void setColor(std::string color);
  // NOTE: : virtual keyword can only be specified inside class definition
  virtual void show();
  virtual int getArea() = 0;
};

#endif
