#include <iostream>

using namespace std;

void func_throw() {
  cout << endl;
  cout << "Inside of func_throw() function" << endl;
  cout << "throw bad_exception" << endl;
  throw std::bad_exception();
  cout << "After throw bad_exception" << endl;
}

void func_2() {
  cout << endl;
  cout << "Inside of func_2() function" << endl;
  cout << "Call func_throw()" << endl;
  func_throw();
  cout << "After func_throw()" << endl;
}

void func_1() {
  cout << endl;
  cout << "Inside of func_1() function" << endl;
  cout << "Call func_2()" << endl;
  func_2();
  cout << "After func_2()" << endl;
}

int main(int argc, char *argv[]) {
  cout << "Inside of main function" << endl;
  try {
    cout << "Call func_1()" << endl;
    func_1();
  } catch (int exec) {
    cout << endl;
    cout << "catch " << exec << endl;
  } catch (const std::bad_exception &e) {
    std::cerr << "Caught " << e.what() << '\n';
  }

  return 0;
}
