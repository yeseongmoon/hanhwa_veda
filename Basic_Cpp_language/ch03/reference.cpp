#include <iostream>

using namespace std;

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

int main(int argc, char *argv[]) {
  int n = 10;

  // NOTE: : reference can only be assigned with variables,
  // but if it's const, it can be e.g. const int &r = 50;
  // If you dont want to modify the reference varaiables,
  // there's no need to use reference variables

  // int &r = n;
  int m = 50;
  // r = m;

  // cout << "r: " << &r << " " << r << endl;
  // cout << "n: " << &n << " " << n << endl;
  // cout << "m: " << &m << " " << m << endl;
  cout << "n: " << n << endl;
  cout << "m: " << m << endl;

  swap(m, n);

  cout << "n: " << n << endl;
  cout << "m: " << m << endl;

  return 0;
}
