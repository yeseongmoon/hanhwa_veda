#include "transportation.h"

Transportation::Transportation() {} // std::cout << "parent constructor\n"; };
Transportation::Transportation(std::string name, int max)
    : transportation_name(name), max_capacity(max) {
  // std::cout << "parent constructor\n";
}
Transportation::~Transportation() {} // std::cout << "parent destructor\n"; }

std::string Transportation::getTransportationName() const {
  return transportation_name;
}

int Transportation::getMaxCapacity() const { return max_capacity; }
