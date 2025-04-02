#include <iomanip>
#include <iostream>
#include <vector>

class Circle {
  int radius;

public:
  Circle(int r) { this->radius = r; }
  ~Circle() {}
  int getRadius() { return this->radius; }
};

int main(int argc, char *argv[]) {
  // // NOTE: : Vector deletes its memory by itself; however,
  // //         if you assign new pointer, you have to delete
  // //         the mmory by yourself
  // std::vector<Circle> vec;
  // for (int i = 0; i < 5; i++) {
  //   Circle c = (i + 10);
  //   vec.push_back(c);
  // }
  //
  // int biggest_r = vec.at(0).getRadius(), idx = 0;
  // for (auto it = vec.begin(); it != vec.end(); it++) {
  //   if (biggest_r < (*it).getRadius()) {
  //     biggest_r = (*it).getRadius();
  //     ++idx;
  //   }
  // }
  //
  // std::cout << "Radius list: " << std::endl;
  // for (auto it = vec.begin(); it != vec.end(); it++) {
  //   std::cout << "Raidus: " << (*it).getRadius() << std::endl;
  // }
  // std::cout << "The biggest radius is " << biggest_r << std::endl;
  // std::cout << "The biggest radius is at " << idx + 1 << std::endl;
  std::vector<int> vec;
  vec.push_back(0);
  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);
  vec.push_back(40);

  vec.insert(vec.begin() + 3, 25);
  std::cout << "Result after insert: " << std::endl;
  for (auto it = vec.begin(); it != vec.end(); it++) {
    std::cout << std::setw(22) << *it << std::endl;
  }
  vec.erase(vec.begin() + 3);
  std::cout << "Result after erase: " << std::endl;
  for (auto it = vec.begin(); it != vec.end(); it++) {
    std::cout << std::setw(22) << *it << std::endl;
  }

  return 0;
}
