#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include <iostream>
#include <string>
using namespace std;

class Employee {
protected:
  string name;
  int empNumber;

public:
  Employee(string name, int empNumber);
  virtual ~Employee();
  virtual int getPay() const = 0;
  void showSalary() const;
};

#endif
