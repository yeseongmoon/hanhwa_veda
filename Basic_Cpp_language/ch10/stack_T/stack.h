#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <string>

template <typename T> class Stack {
  T *stack_ptr;
  int size;
  int top;

public:
  Stack(int size) {
    this->size = size;
    this->top = -1;
    stack_ptr = new T[this->size];
  }
  Stack(const Stack &copy) {
    this->size = copy.size;
    this->top = copy.top;
    stack_ptr = new T[this->size];
    for (int i = 0; i < this->top + 1; i++) {
      stack_ptr[i] = copy.stack_ptr[i];
    }
  }

  ~Stack() { delete[] stack_ptr; }
  T pop() {
    // if (this->top == -1) {
    //   return -1;
    // }
    T temp = stack_ptr[this->top--];

    return temp;
  }
  void push(T input) { stack_ptr[++this->top] = input; }

  int getSize() { return this->size; }
  void setSize(int size) {
    try {
      if (size < 0)
        throw -1;
      int *temp = new T[size];
      for (int i = 0; i < this->size + 1; i++) {
        temp[i] = stack_ptr[i];
      }
      delete[] stack_ptr;
      stack_ptr = temp;
      this->size = size;
    } catch (int e) {
      std::cout << "Negative integer cannot be the size of the array"
                << std::endl;
    }
  }
  int getTop() { return this->top + 1; }
  T getData() {
    // if (this->top == -1)
    //   return -1;
    // else
    return stack_ptr[this->top];
  }
};

#endif
