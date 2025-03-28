#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <string>

class Stack {
  int *stack_ptr;
  int size;
  int top;

public:
  Stack(int size = 10);
  Stack(const Stack &copy);
  ~Stack();
  int pop();
  void push(int num);
  int getSize();
  void setSize(int size);
  int getTop();
  int getData();
};

#endif
