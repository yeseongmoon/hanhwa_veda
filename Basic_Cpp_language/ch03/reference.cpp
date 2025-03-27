#include <iostream>

using namespace std;

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

// NOTE: : Reference to Array for Function Parameter
// You HAVE TO inlcude the exact size of the array
// when passing it to function parameters
void print_ref(int (&p)[5]) {
  for (int i = 0; i < 5; i++) {
    cout << "p: " << p[i] << endl;
  }
}

int main(int argc, char *argv[]) {
  int n = 10;

  // NOTE: : Reference declaration
  // Reference should be assigned when creating and can only be assigned with
  // variables. If it's const, it can be e.g. const int &r = 50; hoever, if you
  // dont want to modify the reference varaiables, there's no need to use
  // reference variables

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

  // NOTE: : Reference to an Array
  // when declaring reference to an array,
  // you need to declare it with (&variable_name)[size of the array]
  // the size of the array should be fixed. It only can be constant numbers
  int num[5] = {1, 2, 3, 4, 5};
  // const int x = 5;
  int (&p)[5] = num;
  print_ref(p);

  return 0;
}
