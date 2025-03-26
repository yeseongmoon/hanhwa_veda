#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  int size;
  cout << "배열의 전체 크기를 입력하세요: ";
  cin >> size;

  int *fibo = new int[size];

  for (int i = 0; i < size; i++) {
    if (i == 0)
      fibo[i] = i;
    else if (i == 1)
      fibo[i] = i;
    else {
      fibo[i] = fibo[i - 2] + fibo[i - 1];
    }
  }

  cout << "Fibonacci Sequence: ";
  for (int i = 0; i < size; i++) {
    cout << fibo[i] << " ";
  }
  cout << endl;

  int idx;
  cout << "몇 번째 숫마다다 출력할까요?:_";
  cin >> idx;

  for (int i = 0; i < size; i++) {
    if (i % idx == 0)
      cout << fibo[i] << endl;
  }
  delete[] fibo;

  return 0;
}
