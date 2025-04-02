#include "manager.h"
#include "regular.h"
#include "sales.h"
#include "temporary.h"

PayCostManager::PayCostManager() {}
PayCostManager::~PayCostManager() {
  for (auto element : empList)
    delete element;
}
void PayCostManager::addPayCost(int type, int pay, int empNumber, string name,
                                int payInfo) {
  switch (type) {
  case 1:
    empList.push_back(new Regular(name, empNumber, pay));
    break;
  case 2:
    empList.push_back(new Temporary(name, empNumber, pay, payInfo));
    break;
  case 3:
    empList.push_back(new Sales(name, empNumber, pay, payInfo));
    break;
  }
} // 급여 정보 등록 함수
  // type 1 : 월 급여 사원, payInfo : 1
  // type 2: 일 급여 사원, payInfo : 근무 일수
  // type 3 : 영업사원, payInfo : 월 매출액

void PayCostManager::showAllPayCost() const {
  for (auto it = empList.begin(); it != empList.end(); it++) {
    (*it)->showSalary();
  }
} // 모든 사원 급여정보 확인 함수

void PayCostManager::showTotalPayCost() const {
  double total_pay;
  for (auto it = empList.begin(); it != empList.end(); it++) {
    total_pay += (*it)->getPay();
  }
  cout << "Total Pay: " << total_pay << endl;
} // 총 지출해야 할 급여 확인 함수
