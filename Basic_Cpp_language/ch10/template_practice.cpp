#include <iostream>

template <class T> T add(T *arr, size_t size) {
  // NOTE: : initialize with T() for all types
  T tmp = T();
  for (int i = 0; i < size; i++)
    tmp += arr[i];
  return tmp;
}

int main(int argc, char *argv[]) {
  int arr1[5] = {1, 2, 3, 4, 5};
  char arr2[2] = {'!', '"'};
  double arr3[5] = {1.2, 2.3, 4.5, 6.6, 1.9};
  std::string arr4[2] = {"hello", "world"};

  std::cout << add(arr1, 5) << std::endl;
  std::cout << add(arr2, 2) << std::endl;
  std::cout << add(arr3, 5) << std::endl;
  std::cout << add(arr4, 2) << std::endl;

  return 0;
}
