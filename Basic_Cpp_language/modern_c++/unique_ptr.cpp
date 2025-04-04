#include "bus.h"
#include <memory>

int main(int argc, char *argv[]) {
  int a = 5;
  std::unique_ptr<int> ptr = std::make_unique<int>(a);
  std::cout << ptr.get() << std::endl;
  std::cout << "*ptr: " << *ptr << std::endl;
  auto ptr1(std::move(ptr));
  std::cout << ptr1.get() << std::endl;
  std::cout << "*ptr: " << *ptr1 << std::endl;
  // NOTE: : now you cannot access ptr.get()
  int *p = ptr1.get();
  *p = 10;
  std::cout << p << std::endl;
  std::vector<std::unique_ptr<Bus>> v;
  v.push_back(std::make_unique<Bus>());
  v.push_back(std::make_unique<Bus>());
  v.push_back(std::make_unique<Bus>());
  v.push_back(std::make_unique<Bus>());
  v.push_back(std::make_unique<Bus>());
  // std::unique_ptr<Bus> ptr = std::make_unique<Bus>();
  // std::cout << "Name: " << ptr->getTransportationName()
  //           << " Capacity: " << ptr->getMaxCapacity() << std::endl;
  return 0;
}
