#include <iostream>

const long double km_per_mile = 1.609344L;

long double operator""_km(long double val) { return val; }
long double operator""_mi(long double val) { return val * km_per_mile; }

int main(int argc, char *argv[]) {
  long double distance_1 = 1.0_km;
  long double distance_2 = 1.0_mi;
  std::cout << distance_1 + distance_2 << " km" << std::endl;
  return 0;
}
