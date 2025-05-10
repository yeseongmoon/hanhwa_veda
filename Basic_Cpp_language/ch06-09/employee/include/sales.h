#ifndef _SALES_H_
#define _SALES_H_

#include "employee.h"

class Sales : public Employee {
  int basePay;
  int extraPay;
  int total_sales;

public:
  Sales(string name, int empNumber, int basePay, int total_sales);
  virtual ~Sales();
  int getPay() const override;
};

#endif
