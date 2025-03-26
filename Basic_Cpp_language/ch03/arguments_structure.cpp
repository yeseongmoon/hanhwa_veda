#include <iostream>

using namespace std;

struct Person {
  std::string name;
  int age;
  float height;
  float weight;
};

void check_age(Person _adult[], int _count) {
  for (int i = 0; i < _count; i++) {
    if (_adult[i].age >= 25) {
      cout << "name: " << _adult[i].name << endl;
      cout << "age: " << _adult[i].age << endl;
      cout << "height: " << _adult[i].height << endl;
      cout << "weight: " << _adult[i].weight << endl;
    }
  }
  _count++;
}

int main(int argc, char *argv[]) {
  string name_info[10] = {"Brain", "Jessica", "James", "Eric", "John",
                          "Tom",   "Tomy",    "Alice", "Bob",  "Carol"};
  int age_info[10] = {24, 22, 30, 28, 35, 40, 25, 27, 32, 29};
  float height_info[10] = {180, 165, 170, 172, 168, 175, 169, 181, 163, 177};
  float weight_info[10] = {70, 55, 65, 68, 62, 75, 57, 73, 60, 80};

  int person_num;
  cout << "Enter the size of the Person array(<= 10): ";
  cin >> person_num;
  if (person_num < 0)
    exit(0);
  if (person_num > 10)
    person_num = 10;

  Person *adult = new Person[person_num];
  if (adult == nullptr)
    exit(0);

  for (int i = 0; i < person_num; i++) {
    adult[i].name = name_info[i];
    adult[i].age = age_info[i];
    adult[i].height = height_info[i];
    adult[i].weight = weight_info[i];
  }

  check_age(adult, person_num);
  delete[] adult;

  return 0;
}
