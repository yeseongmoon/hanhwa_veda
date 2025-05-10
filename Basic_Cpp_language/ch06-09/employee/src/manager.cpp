#include "manager.h"
#include "regular.h"
#include "sales.h"
#include "temporary.h"

PayCostManager::PayCostManager() {}
PayCostManager::~PayCostManager() {
  for (int i = 0; i < empNum; i++)
    delete empList[i];
}
void PayCostManager::addPayCost(int type, int pay, int empNumber, string name,
                                int payInfo) {
  switch (type) {
  case 1:
    empList[empNum++] = new Regular(name, empNumber, pay);
    break;
  case 2:
    empList[empNum++] = new Temporary(name, empNumber, pay, payInfo);
    break;
  case 3:
    empList[empNum++] = new Sales(name, empNumber, pay, payInfo);
    break;
  }
} // 급여 정보 등록 함수
  // type 1 : 월 급여 사원, payInfo : 1
  // type 2: 일 급여 사원, payInfo : 근무 일수
  // type 3 : 영업사원, payInfo : 월 매출액

void PayCostManager::showAllPayCost() const {
  for (int i = 0; i < empNum; i++) {
    empList[i]->showSalary();
  }
} // 모든 사원 급여정보 확인 함수

void PayCostManager::showTotalPayCost() const {
  double total_pay;
  for (int i = 0; i < empNum; i++) {
    total_pay += empList[i]->getPay();
  }
  cout << "Total Pay: " << total_pay << endl;
} // 총 지출해야 할 급여 확인 함수
