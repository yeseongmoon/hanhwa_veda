#include <iostream>
#include <map>

int main(int argc, char *argv[]) {
  std::map<std::string, int> m;
  m.insert({"redd", 0});
  auto a = m.find("edd");
  if (a == m.end()) {
    std::cout << "not found\n";
  }
  return 0;
}
