#include <iostream>

int main(int argc, char *argv[]) {
  int num;

  std::cout << "좋아하는 숫자를 입력하세요:_";
  std::cin >> num;

  std::cout << "입력한 숫자는 " << num << " 입니다." << std::endl;

  return 0;
}
