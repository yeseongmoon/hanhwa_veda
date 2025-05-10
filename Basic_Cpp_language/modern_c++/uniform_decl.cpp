#include <iostream>
#include <vector>
struct S {
  std::string name;
  float num;
  S(std::string s, float f) : name(s), num(f) {}
};

int main(int argc, char *argv[]) {
  std::vector<S> v{{"John", 20}, {"Peter", 30}, {"Max", 40}};
  for (auto it : v) {
    std::cout << it.name << " " << it.num << std::endl;
  }
  return 0;
}
