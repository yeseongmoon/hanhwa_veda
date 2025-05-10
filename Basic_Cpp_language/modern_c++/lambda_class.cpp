#include "transportation.h"
#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<Transportation> v = {
      Transportation("bus", 40), Transportation("electric scooter", 1),
      Transportation("subway", 1000), Transportation("taxi", 5)};

  std::string input;
  std::cout << "What transporation do you want to know the max capacity? ";
  std::cin >> input;
  auto result = find_if(v.begin(), v.end(), [=](Transportation t) {
    return t.getTransportationName() == input;
  });

  std::cout << "The max capacity is " << result->getMaxCapacity() << std::endl;

  return 0;
}
