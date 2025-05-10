#include "stack.h"

int main(int argc, char *argv[]) {
  Stack<std::string> s(3);
  Stack<char> c(3);
  Stack<int> i(3);
  Stack<double> d(3);

  s.push("ABC");
  s.push("DEF");
  s.push("GHI");

  c.push('a');
  c.push('b');
  c.push('c');

  i.push(1);
  i.push(2);
  i.push(3);

  d.push(1.2);
  d.push(2.2);
  d.push(3.2);

  std::cout << "string:\n";
  std::cout << "getData: " << s.getData() << std::endl;
  std::cout << "pop: " << s.pop() << std::endl;
  std::cout << "getData: " << s.getData() << std::endl;
  std::cout << "getTop: " << s.getTop() << std::endl;

  std::cout << "char:\n";
  std::cout << "getData: " << c.getData() << std::endl;
  std::cout << "pop: " << c.pop() << std::endl;
  std::cout << "getData: " << c.getData() << std::endl;
  std::cout << "getTop: " << c.getTop() << std::endl;

  std::cout << "integer:\n";
  std::cout << "getData: " << i.getData() << std::endl;
  std::cout << "pop: " << i.pop() << std::endl;
  std::cout << "getData: " << i.getData() << std::endl;
  std::cout << "getTop: " << i.getTop() << std::endl;

  std::cout << "doubel:\n";
  std::cout << "getData: " << d.getData() << std::endl;
  std::cout << "pop: " << d.pop() << std::endl;
  std::cout << "getData: " << d.getData() << std::endl;
  std::cout << "getTop: " << d.getTop() << std::endl;
  return 0;
}
