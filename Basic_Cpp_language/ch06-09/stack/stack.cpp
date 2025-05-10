#include "stack.h"

Stack::Stack(int size) {
  this->size = size;
  this->top = -1;
  stack_ptr = new int[this->size]();
}
Stack::Stack(const Stack &copy) {
  this->size = copy.size;
  this->top = copy.top;
  stack_ptr = new int[this->size];
  for (int i = 0; i < this->top + 1; i++) {
    stack_ptr[i] = copy.stack_ptr[i];
  }
}

Stack::~Stack() { delete[] stack_ptr; }

int Stack::pop() {
  if (this->top == -1) {
    return -1;
  }
  int temp = stack_ptr[this->top--];

  return temp;
}

// FIX: need to fix this function that checks if the stack is full
void Stack::push(int num) { stack_ptr[++this->top] = num; }

int Stack::getSize() { return this->size; }

void Stack::setSize(int size) {
  try {
    if (size < 0)
      throw -1;
    int *temp = new int[size];
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

int Stack::getTop() { return this->top; }

int Stack::getData() {
  if (this->top == -1)
    return -1;
  else
    return stack_ptr[this->top];
}
