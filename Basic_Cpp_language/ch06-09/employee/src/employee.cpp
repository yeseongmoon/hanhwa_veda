#include "employee.h"

Employee::Employee(string name, int empNumber) {
  this->name = name;
  this->empNumber = empNumber;
}

Employee::~Employee() {}
void Employee::showSalary() const {
  cout << "Employee Name : " << name << endl;
  cout << "Employee number : " << empNumber << endl;
  cout << "Employee's Salary : " << getPay() << endl << endl;
}
