#include <iostream>
#include <map>
#include <set>

int main(int argc, char *argv[]) {
  std::multimap<std::string, int> scores;

  // NOTE: : std::make_pair = {"", int}
  scores.insert({"Bob", 85});
  scores.insert({"Jane", 90});
  scores.insert({"Tom", 70});
  scores.insert({"Bob", 100});
  // NOTE: multimap doesn't support this feature:
  // scores["Ben"] = 66;

  std::cout << "Size of the multmap: " << scores.size() << std::endl;

  int count = scores.count("Bob");
  std::cout << "Bob's scores that are saved: " << count << std::endl;

  auto range = scores.equal_range("Bob");
  if (range.first != scores.end()) {
    std::cout << "Bob's score: " << std::endl;
    for (auto it = range.first; it != range.second; ++it)
      std::cout << it->second << " ";
    std::cout << std::endl;
  } else
    std::cout << "Bob's score not stored" << std::endl;

  scores.erase("Bob");
  std::cout << "Size of the multimap after erasing Bob's score: "
            << scores.size() << std::endl
            << std::endl;
  std::cout << "----all the element of the map----" << std::endl;

  for (const auto &pair : scores) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }

  return 0;
}
