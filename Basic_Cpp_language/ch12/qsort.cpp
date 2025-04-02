#include <algorithm>
#include <iostream>
#include <vector>

int comp(const void *a, const void *b) { return *(int *)a > *(int *)b; }

template <typename T> void print_vector_all(std::vector<T> &vec) {
  for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end();
       it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  std::vector<int> vec = {7, 6, 3, 5, 4, 1, 2, 0, 8};
  sort(vec.begin(), vec.end(), std::greater<int>());
  print_vector_all(vec);
  sort(vec.begin(), vec.end(), std::less<int>());
  print_vector_all(vec);
  return 0;
}
