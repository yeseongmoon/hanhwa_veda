#ifndef _REGULAR_H_
#define _REGULAR_H_

#include "employee.h"

class Regular : public Employee {
  int salary;

public:
  Regular(string name, int empNumber, int salary);
  virtual ~Regular();
  int getPay() const override;
};

#endif
