#include <iostream>
#include <typeinfo>
using namespace std;
class Shape {
public:
  virtual void Draw() { cout << "Drawing a shape." << endl; }
};
class Circle : public Shape {
public:
  void Draw() override { cout << "Drawing a circle." << endl; }
};
int main() {
  Shape *shapePtr = new Shape();
  if (typeid(*shapePtr) == typeid(Circle)) {
    cout << "Shape is a Circle." << endl;
  } else {
    cout << "Shape is not a Circle." << endl;
  }
  Circle *circlePtr = dynamic_cast<Circle *>(shapePtr);
  // Circle* circlePtr = (Circle*) (shapePtr);
  if (circlePtr != nullptr) {
    circlePtr->Draw();
  } else
    cout << "Downcast fail" << endl;
  delete shapePtr;

  Circle *circlePtr1 = new Circle();
  Shape *shapePtr1 = dynamic_cast<Shape *>(circlePtr1);
  // Circle* circlePtr = (Circle*) (shapePtr);
  if (shapePtr1 != nullptr) {
    shapePtr1->Draw();
  } else
    cout << "Upcast fail" << endl;
  delete circlePtr1;
  return 0;
}
