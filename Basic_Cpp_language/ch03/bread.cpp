#include <iostream>

int main(int argc, char *argv[]) {
  int customer_num = 0;
  std::cout << "Today's customer: ";
  std::cin >> customer_num;

  std::string *bread = new std::string[customer_num];
  if (bread == nullptr) {
    exit(0);
  }
  for (int i = 0; i < customer_num; i++) {
    bread[i] = "bread_" + std::to_string(i + 1);
  }

  std::cout << "-- bread --" << std::endl;
  for (int i = 0; i < customer_num; i++) {
    std::cout << bread[i] << std::endl;
  }

  delete[] bread;

  return 0;
}
