#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  try {
    int input;
    cout << "Enter one integer: ";
    cin >> input;

    if (input > 0) {
      cout << "Throw 1" << endl;
      throw 1;
      cout << "After throw 1" << endl;
    }
    if (input < 0) {
      cout << "Throw -1.0f" << endl;
      throw -1.0f;
      cout << "After throw -1.0f" << endl;
    }
    if (input == 0) {
      cout << "Throw Z" << endl;
      throw 'Z';
      cout << "After throw Z" << endl;
    }

  } catch (int a) {
    cout << "Catch " << a << endl;
  } catch (...) {
    cout << "Catch all" << endl;
  }
  return 0;
}
