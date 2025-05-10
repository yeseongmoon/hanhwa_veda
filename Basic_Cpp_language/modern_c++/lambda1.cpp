#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  auto add = [](int n1, int n2) -> int { return n1 + n2; };
  std::cout << add(10, 20) << std::endl;

  int x = 10;
  auto f = [=](int n1, int n2) mutable -> int {
    x = 100;
    return n1 + n2;
  };
  f(2, 5);
  std::cout << x << std::endl;

  std::vector<int> v{1, 2, 3, 4, 5};
  int z = 2, y = 4;
  // auto result =
  //     find_if(begin(v), end(v), [=](int i) { return i > z && i < y; });
  std::for_each(v.begin(), v.end(), [](int &n) { n *= 2; });
  for (auto it : v)
    std::cout << it << " ";
  std::cout << std::endl;

  return 0;
}
