#ifndef __TRANSPORTATION_H_
#define __TRANSPORTATION_H_

#include <iostream>

class Transportation {
  std::string transportation_name;
  int max_capacity;

public:
  Transportation();
  Transportation(std::string name, int max);
  ~Transportation();
  std::string getTransportationName() const;
  int getMaxCapacity() const;
};

#endif
