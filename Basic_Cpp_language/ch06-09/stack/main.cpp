#include "stack.h"

int main(int argc, char *argv[]) {
  Stack s;
  std::cout << s.getSize() << std::endl;
  std::cout << s.getData() << std::endl;
  s.push(1);
  std::cout << s.getData() << std::endl;

  for (int i = 10; i <= 20; i++) {
    s.push(i);
  }

  std::cout << "getData: " << s.getData() << std::endl;
  std::cout << "pop: " << s.pop() << std::endl;
  std::cout << "getData: " << s.getData() << std::endl;
  std::cout << "getTop: " << s.getTop() << std::endl;

  s.setSize(20);
  Stack t(s);
  for (int i = 0; i < 9; i++) {
    std::cout << t.pop() << std::endl;
  }

  return 0;
}
