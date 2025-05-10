#include <iostream>
#include <typeinfo>

template <typename I, typename J> auto add(I i, J j) -> decltype(i + j) {
  return i + j;
}

auto main() -> int {
  std::cout << "[auto.cpp]" << std::endl;
  // 여러 개의 auto 타입 변수를 생성
  auto a = 1;
  auto b = 1.0;
  auto c = a + b;
  auto d = {b, c};
  // 변수의 실제 타입을 출력
  std::cout << "type of a : " << typeid(a).name() << std::endl;
  std::cout << "type of b : " << typeid(b).name() << std::endl;
  std::cout << "type of c : " << typeid(c).name() << std::endl;
  std::cout << "type of d : " << typeid(d).name() << std::endl;

  auto e = add<int, double>(2, 2.5);
  std::cout << "result of 2 + 2.5 = " << e << std::endl;

  auto f = add<int, int>(10, 20);
  std::cout << "result of 10 + 20 = " << f << std::endl;

  auto g = add<char, char>('!', '=');
  std::cout << "result of ! + = = " << g << std::endl;

  auto h = add<std::string, std::string>("hello ", "world");
  std::cout << "result of hello  + world = " << h << std::endl;

  return 0;
}
