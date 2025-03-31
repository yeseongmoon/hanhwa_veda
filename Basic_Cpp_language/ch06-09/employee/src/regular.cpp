#include "regular.h"
Regular::Regular(string name, int empNumber, int salary)
    : Employee(name, empNumber), salary(salary) {}

Regular::~Regular() {}

int Regular::getPay() const { return salary; }
