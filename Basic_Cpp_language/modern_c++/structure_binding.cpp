#include <iostream>
#include <map>
#include <tuple>

using namespace std;

struct data_struct {
  int number;
  string sentence;
  float decimal;
};

int main() {
  int numbers[3] = {1, 2, 3};
  auto [number0, number1, number2] = numbers;
  cout << "A structural binding of an array" << endl;
  cout << numbers[0] << " : " << number0 << endl;
  cout << numbers[1] << " : " << number1 << endl;
  cout << numbers[2] << " : " << number1 << endl;

  struct data_struct struct_object{20, "structure", 10.5f};
  auto [number3, string0, decimal0] = struct_object;
  cout << endl << "A structural binding of a structure" << endl;
  cout << struct_object.number << " : " << number3 << endl;
  cout << struct_object.sentence << " : " << string0 << endl;
  cout << struct_object.decimal << " : " << decimal0 << endl;

  tuple<int, char, double> tuple_object{5, 'C', 20.1f};
  auto [number4, char1, decimal1] = tuple_object;
  cout << endl << "A structural binding of a tuple" << endl;
  cout << get<0>(tuple_object) << " : " << number4 << endl;
  cout << get<1>(tuple_object) << " : " << char1 << endl;
  cout << get<2>(tuple_object) << " : " << decimal1 << endl;

  map<int, string> map_object{{0, "first"}, {1, "second"}, {2, "third"}};
  cout << endl << "A structural binding of a map" << endl;
  for (auto [number5, string1] : map_object) {
    cout << "[" << number5 << "] " << map_object[number5] << " : " << string1
         << endl;
  }
}
