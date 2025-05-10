#include <iostream>
using namespace std;
class Base {
  int a;

protected:
  void setA(int a) { this->a = a; }

public:
  void ShowA() { cout << a; }
};

class Derived : private Base {
  int b;

protected:
  void setB(int b) { this->b = b; }

public:
  void ShowB() {
    a = 3;
    setA(5);
    ShowA();
    cout << b;
  }
};

class GrandDerived : private Derived {
  int c;

protected:
  void setAB(int x) {
    setA(x);
    ShowA();
    setB(x);
  }
};
