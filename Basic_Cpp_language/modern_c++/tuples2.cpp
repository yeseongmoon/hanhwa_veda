#include <iostream>
#include <tuple>

using namespace std;

tuple<int, string, bool> getItem(int pos) {
  if (pos == 0)
    return make_tuple<int, string, bool>(1, "Robert", true);
  else if (pos == 1)
    return make_tuple<int, string, bool>(2, "Anna", false);
  else if (pos == 2)
    return make_tuple<int, string, bool>(3, "AJ", true);

  return make_tuple<int, string, bool>(0, "", false);
}

auto main() -> int {
  // 두 개의 튜플 초기화
  // id name boolean

  auto t1 = getItem(0);
  auto t2 = getItem(1);
  auto t3 = getItem(2);
  int i;
  string s;
  bool b;

  // t1 에서 값 추출
  tie(i, s, b) = t1; // tie() : 튜플이나 페어에서 값 추출할 때 사용
  cout << "tie(i, s, b) = t1\n";
  cout << "i = " << i << endl;
  cout << "s = " << s << endl;
  cout << "b = " << boolalpha << b << endl;
  cout << endl;

  // t2에서 값 추출
  // tie(ignore, s, ignore) = t2;
  tie(i, s, b) = t2;
  cout << "tie(ignore, s, ignore) = t1\n";
  cout << "new i = " << i << endl;
  cout << "new s = " << s << endl;
  cout << "new b = " << boolalpha << b << endl;
  cout << endl;

  tie(i, s, b) = t3;
  cout << "tie(ignore, s, ignore) = t1\n";
  cout << "new i = " << i << endl;
  cout << "new s = " << s << endl;
  cout << "new b = " << boolalpha << b << endl;
  cout << endl;
  return 0;
}
