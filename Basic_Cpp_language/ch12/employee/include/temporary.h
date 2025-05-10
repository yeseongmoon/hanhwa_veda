#ifndef _TEMPORARY_H_
#define _TEMPORARY_H_

#include "employee.h"

class Temporary : public Employee {
  int wage;
  int workDay;

public:
  Temporary(string name, int empNumber, int wage, int workDay);
  virtual ~Temporary();
  int getPay() const override;
};

#endif
