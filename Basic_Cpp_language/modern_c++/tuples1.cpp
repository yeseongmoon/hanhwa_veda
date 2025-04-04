#include <tuple>
#include <iostream>

using namespace std;

auto main() -> int
{
	// 두 개의 튜플 초기화
	tuple<int, string, bool> t1(1, "Robert", true);
	auto t2 = make_tuple(2, "Anna", false);

	// t1 요소 출력
	cout << "t1 elements : " << endl;
	cout << get<0>(t1) << endl;		// get<인덱스>(튜플객체) : 튜플의 각 요소 값을 읽어옴
	cout << get<1>(t1) << endl;
	cout << ( get<2>(t1)==true? "Male":"Female") << endl;
	cout << endl;

	// t2 요소 출력
	cout << "t2 elements : " << endl;
	cout << get<0>(t2) << endl;
	cout << get<1>(t2) << endl;
	cout << (get<2>(t2) == true ? "Male" : "Female") << endl;
	cout << endl;

	return 0;
}