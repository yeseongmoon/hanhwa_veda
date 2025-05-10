#include <iostream>
#include <string>

void check_found(std::string::size_type n) {
  if (n == std::string::npos) {
    std::cout << "not found" << std::endl;
  } else {
    std::cout << "found index: " << n << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::string str1("Hello");
  str1.append(" World!");
  std::cout << str1 << std::endl;
  std::cout << std::boolalpha;
  std::cout << str1.empty() << std::endl;
  std::string str2("Hello");
  str2.append(" World!", 0, 6);
  std::cout << str2 << std::endl;

  std::string::size_type n;
  std::string str = "This is an example of a standard string";
  n = str.find("example");
  check_found(n);

  std::string strr = "Hello, World!";
  std::cout << "Original string: " << strr << std::endl;

  strr.replace(7, 5, "C+ + ");
  std::cout << "Replaced string: " << strr << std::endl;

  return 0;
}
