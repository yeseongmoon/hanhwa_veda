#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Person {
  std::string name;
  int age;
  float height;
  float weight;
};

void print_person_all(std::vector<Person> &vec) {
  for (std::vector<Person>::iterator it = vec.begin(); it != vec.end(); it++)
    std::cout << "Name: " << it->name << "\t > " << "age : " << it->age << ", "
              << "height : " << it->height << ", " << "weight : " << it->weight
              << std::endl;
}

bool compare(const Person &lhs, const Person &rhs) { return lhs.age < rhs.age; }

int main(int argc, char *argv[]) {
  Person p[5] = {
      {"Brian", 24, 180, 70}, {"Jessica", 22, 165, 55}, {"James", 30, 170, 65},
      {"Tom", 12, 155, 46},   {"Marry", 18, 172, 62},
  };

  std::vector<Person> vec;
  for (int i = 0; i < 5; i++) {
    vec.push_back(p[i]);
  }

  std::cout << "----before sorting----" << std::endl;
  print_person_all(vec);
  std::cout << std::endl;

  sort(vec.begin(), vec.end(), compare);
  std::cout << "----after sorting----" << std::endl;
  print_person_all(vec);

  return 0;
}
