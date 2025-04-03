#include <functional>
#include <iostream>

using namespace std;

// struct bomb {
//   void operator()() { cout << "꽝!" << endl; }
//   void operator()(int range) {
//     cout << "반경 " << range << "m 내 플레이어 공격!" << endl;
//   }
// };
//
// int main() {
//   bomb mine;
//   mine();
//   mine(30);
//   return 0;
// }

void function_pointer(int input) {
  cout << "함수 포인터 대상 함수 : " << input << endl;
}

struct functor {
  void operator()(char functor_prefix) {
    cout << "함자 : " << functor_prefix << endl;
  }
};

class class_object {
public:
  class_object(string init_string) : class_object_name(init_string) {}

  void std_function_call_member(string contents) {
    cout << "클래스 멤버 함수 객체화 (" << class_object_name
         << ") : " << contents << endl;
  }

private:
  string class_object_name;
};

int main() {
  class_object class_obj("호출 객체를 가지고 있는 클래스");
  functor functor_obj;
  function<void(int)> func_pointer = function_pointer;
  function<void(functor &, char)> functor_func = &functor::operator();
  function<void(double)> lambda_func = [](double input) {
    cout << "람다 함수 : " << input << endl;
  };
  function<void(class_object &, string)> member_func =
      &class_object::std_function_call_member;
  func_pointer(10);
  functor_func(functor_obj, 'A');
  lambda_func(0xa8);
  member_func(class_obj, "출력");
  return 0;
}
