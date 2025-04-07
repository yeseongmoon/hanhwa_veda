#include "manager.h"
#include <string>

int main(void) {
  PayCostManager m;
  // Employee *emp[] = {
  //     new Regular("Peter", 10000, 800),    new Regular("Max", 10001, 950),
  //     new Regular("John", 10001, 950),     new Regular("David", 10002, 780),
  //     new Regular("Derrek", 10005, 650),   new Temporary("Jack", 10006, 10,
  //     4), new Temporary("Phil", 10007, 10, 5), new Temporary("Tom", 10008,
  //     10, 6), new Temporary("Tim", 10009, 10, 9),  new Temporary("Cat",
  //     10010, 10, 10)};

  m.addPayCost(1, 800, 10000, "Peter");
  m.addPayCost(1, 800, 10001, "Max");
  m.addPayCost(2, 10, 10002, "John", 10);
  m.addPayCost(2, 10, 10003, "Jack", 20);
  m.addPayCost(3, 200, 10004, "David", 36000);
  m.addPayCost(3, 200, 10005, "Tim", 34000);

  m.showAllPayCost();
  m.showTotalPayCost();
  // FIX: can you fix this not adding another function to the class?
  m.getBonus();

  //
  // for (int i = 0; i < 10; i++)
  //   emp[i]->showSalary();
  //
  // int totalSalary = 0;
  // for (int i = 0; i < 10; i++)
  //   totalSalary += emp[i]->getPay();
  //
  // cout << "Total salary : " << totalSalary << endl;
  //
  // for (int i = 0; i < 10; ++i) {
  //   delete emp[i];
  // }

  return 0;
}
