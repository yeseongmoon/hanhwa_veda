#include <iostream>

using namespace std;

int GetMin(int a, int b) { return a > b ? b : a; }

double GetMin(double a, double b) { return a > b ? b : a; }

string GetMin(string a, string b) { return a > b ? b : a; }

int GetMin(int arr[], int size) {
  int min = arr[0];
  for (int i = 0; i < size; i++) {
    if (min > arr[i]) {
      min = arr[i];
    }
  }
  return min;
}

int main() {
  int a, b;
  cout << "두개의 정수를 입력하세요 : ";
  cin >> a >> b;
  cout << "최소값은 " << GetMin(a, b) << "입니다.\n";
  double c, d;
  cout << "두개의 실수를 입력하세요 : ";
  cin >> c >> d;
  cout << "최소값은 " << GetMin(c, d) << "입니다.\n";
  string s1, s2;
  cout << "두개의 문자열을 입력하세요 : ";
  cin >> s1 >> s2;
  cout << "최소값은 " << GetMin(s1, s2) << "입니다.\n";
  int arr[] = {2, 19, 34, 387, 1, 45, 78, 45, 11, 29};
  cout << "배열의 원소 : ";
  for (int i = 0; i < 10; i++)
    cout << arr[i] << " ";
  cout << "\n최소값은 " << GetMin(arr, 10) << "입니다.\n";
  return 0;
}
