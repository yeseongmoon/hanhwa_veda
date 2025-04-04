#include "transportation.h"
#include <iostream>
#include <memory>
#include <vector>

class Node {
public:
  std::weak_ptr<Node> next;
  Node() { std::cout << "Node created\n"; }
  ~Node() { std::cout << "Node destroyed\n"; }
};

int main() {
  // std::shared_ptr<Node> node1 = std::make_shared<Node>();
  // std::shared_ptr<Node> node2 = std::make_shared<Node>();
  // node1->next = node2;
  // node2->next = node1;

  std::vector<std::shared_ptr<Transportation>> v{
      std::make_shared<Transportation>("bus", 40),
      std::make_shared<Transportation>("taxi", 5),
      std::make_shared<Transportation>("subway", 1000),
      std::make_shared<Transportation>("bike", 1),
      std::make_shared<Transportation>("airplane", 1500)};

  std::string input;
  std::cout << "Enter the transportation name: ";
  std::cin >> input;
  auto result =
      find_if(v.begin(), v.end(), [=](std::shared_ptr<Transportation> v) {
        return input == v->getTransportationName();
      });
  std::cout << "The max capacity is " << (*result)->getMaxCapacity()
            << std::endl;

  // std::shared_ptr<int> ptr1 = std::make_shared<int>(1);
  // std::weak_ptr<int> ptr2 = ptr1;
  // std::cout << "ptr1/ptr2 use_count" << std::endl;
  // std::cout << ptr1.use_count() << std::endl;
  // std::cout << ptr2.use_count() << std::endl;
  // *ptr1 = 100;
  // std::cout << "*ptr1 = " << *ptr1 << std::endl;
  // std::cout << "*ptr2 = " << *(ptr2.lock()) << std::endl;
  // // weakpointer의 lock() : sharedpinter의 주소 반환
  return 0;
}
