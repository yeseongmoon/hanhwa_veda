#include "sales.h"

Sales::Sales(string name, int empNumber, int basePay, int total_sales)
    : Employee(name, empNumber), basePay(basePay), total_sales(total_sales) {}

Sales::~Sales() {}
int Sales::getPay() const {
  int extraPay = total_sales / 10;
  return basePay + extraPay;
}
