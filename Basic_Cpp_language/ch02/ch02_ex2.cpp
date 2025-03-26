#include <iostream>

int main(int argc, char *argv[]) {
  short num1, num2, num3, num4, num5;
  short ans1, ans2, ans3;
  // 0001 0010 0100 1000 10000
  num1 = 1, num2 = 2, num3 = 4, num4 = 8, num5 = 16;
  ans1 |= num1;
  ans1 |= num3;
  ans2 = 24, ans3 = 13;

  std::cout << std::boolalpha;
  std::cout << "ans1 AND num3: " << static_cast<bool>(ans1 & num3) << std::endl;
  std::cout << "ans1 AND num4: " << static_cast<bool>(ans1 & num4) << std::endl;
  std::cout << "ans2 AND num2: " << static_cast<bool>(ans2 & num2) << std::endl;
  std::cout << "ans2 AND num4: " << static_cast<bool>(ans2 & num4) << std::endl;
  std::cout << "ans3 AND num1: " << static_cast<bool>(ans3 & num1) << std::endl;
  std::cout << "ans3 AND num5: " << static_cast<bool>(ans3 & num5) << std::endl;
  std::cout << std::endl;

  std::cout << "ans1 AND num3: " << (ans1 & num3) << std::endl;
  std::cout << "ans1 AND num4: " << (ans1 & num4) << std::endl;
  std::cout << "ans2 AND num2: " << (ans2 & num2) << std::endl;
  std::cout << "ans2 AND num4: " << (ans2 & num4) << std::endl;
  std::cout << "ans3 AND num1: " << (ans3 & num1) << std::endl;
  std::cout << "ans3 AND num5: " << (ans3 & num5) << std::endl;

  return 0;
}
