#include "temporary.h"
Temporary::Temporary(string name, int empNumber, int wage, int workDay)
    : Employee(name, empNumber), wage(wage), workDay(workDay) {}

Temporary::~Temporary() {}

int Temporary::getPay() const { return workDay * wage; }
