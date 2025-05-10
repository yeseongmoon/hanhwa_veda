#include <tuple>
#include <iostream>

using namespace std;

auto main() -> int
{
	// �� ���� Ʃ�� �ʱ�ȭ
	tuple<int, string, bool> t1(1, "Robert", true);
	auto t2 = make_tuple(2, "Anna", false);

	// t1 ��� ���
	cout << "t1 elements : " << endl;
	cout << get<0>(t1) << endl;		// get<�ε���>(Ʃ�ð�ü) : Ʃ���� �� ��� ���� �о��
	cout << get<1>(t1) << endl;
	cout << ( get<2>(t1)==true? "Male":"Female") << endl;
	cout << endl;

	// t2 ��� ���
	cout << "t2 elements : " << endl;
	cout << get<0>(t2) << endl;
	cout << get<1>(t2) << endl;
	cout << (get<2>(t2) == true ? "Male" : "Female") << endl;
	cout << endl;

	return 0;
}