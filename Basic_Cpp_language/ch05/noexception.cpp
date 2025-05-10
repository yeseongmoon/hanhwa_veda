#include <iostream>

void real_noexcept() noexcept { std::cout << "real_noexcept" << std::endl; }

void fake_noexcept() noexcept {
  std::cout << "fake_noexcept" << std::endl;
  throw 1;
}

int main(int argc, char *argv[]) {
  real_noexcept();

  try {
    fake_noexcept();
  } catch (int exec) {
    std::cout << "catch " << exec << std::endl;
  }

  return 0;
}
