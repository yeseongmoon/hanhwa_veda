#include <iomanip>
#include <iostream>
#include <map>

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  std::map<std::string, int> tree;
  std::string input;
  int count = 0;
  while (std::getline(std::cin, input)) {
    tree[input] += 1;
    count++;
  }
  for (auto &it : tree) {
    std::cout << it.first << " " << std::fixed << std::setprecision(4)
              << (static_cast<float>(it.second) / count) * 100 << "\n";
  }
  return 0;
}
