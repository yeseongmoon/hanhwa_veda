#include <algorithm>
#include <iostream>
#include <vector>

class Circle {
  int radius;

public:
  Circle(int r) { this->radius = r; }
  ~Circle() {}
  int getRadius() const { return this->radius; }

  // NOTE: : for find function
  bool operator==(const Circle &other) const {
    return radius == other.getRadius();
  }
};

bool compare(const Circle &a, const Circle &b) {
  return a.getRadius() < b.getRadius();
}

int main(int argc, char *argv[]) {
  // std::vector<int> numbers = {1, 2, 3, 4, 5};
  // std::cout << "Number: ";
  // int target;
  // std::cin >> target;
  //
  // std::vector<int>::iterator it = find(numbers.begin(), numbers.end(),
  // target); if (it != numbers.end())
  //   std::cout << "index: " << std::distance(numbers.begin(), it) <<
  //   std::endl;
  // else
  //   std::cout << "No such number\n";
  std::vector<Circle> circles = {{10}, {52}, {65}, {22}, {17}, {80}, {99}};
  // NOTE: :find function compares all the elements; thus, performance can be
  // bad
  // std::vector<Circle>::iterator it =
  //     find(circles.begin(), circles.end(), Circle{80});

  // if (it != circles.end())
  //   std::cout << "index: " << std::distance(circles.begin(), it) <<
  //   std::endl;
  // else
  //   std::cout << "No such radius existed\n";

  sort(circles.begin(), circles.end(), compare);
  int target;
  std::cout << "target num: ";
  std::cin >> target;

  bool found =
      std::binary_search(circles.begin(), circles.end(), target, compare);
  if (found)
    std::cout << "target found!" << std::endl;
  else
    std::cout << "target not found!" << std::endl;

  return 0;
}
