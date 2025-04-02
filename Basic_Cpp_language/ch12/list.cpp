#include <iostream>
#include <list>
class Circle {
  int radius;

public:
  Circle(int r) { this->radius = r; }
  ~Circle() {}
  int getRadius() { return this->radius; }
};
int main(int argc, char *argv[]) {
  std::list<Circle> circle_list;
  for (int i = 0; i < 5; i++) {
    circle_list.push_back(Circle(i + 10));
  }

  std::cout << "Circle List: " << std::endl;
  for (auto it = circle_list.begin(); it != circle_list.end(); it++) {
    std::cout << (*it).getRadius() << std::endl;
  }

  std::cout << "First element: " << circle_list.front().getRadius()
            << std::endl;
  std::cout << "Last element: " << circle_list.back().getRadius() << std::endl;

  circle_list.push_front(Circle(25));
  std::cout << "After push_front(Circle(25))" << std::endl;
  std::cout << "First element: " << circle_list.front().getRadius()
            << std::endl;
  std::cout << "Last element: " << circle_list.back().getRadius() << std::endl;

  circle_list.pop_back();
  std::cout << "After pop_back()" << std::endl;
  std::cout << "First element: " << circle_list.front().getRadius()
            << std::endl;
  std::cout << "Last element: " << circle_list.back().getRadius() << std::endl;

  circle_list.pop_front();
  std::cout << "After pop_front()" << std::endl;
  std::cout << "First element: " << circle_list.front().getRadius()
            << std::endl;
  std::cout << "Last element: " << circle_list.back().getRadius() << std::endl;

  return 0;
}
