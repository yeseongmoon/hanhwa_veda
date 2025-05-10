#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "employee.h"

class PayCostManager {
private:
  Employee *empList[50]; // 사원 정보 관리 배열, 최대 인원 50명
  static int empNum;     // 사원 수
public:
  PayCostManager();
  ~PayCostManager();
  void addPayCost(int type, int pay, int empNumber, string name,
                  int payInfo = 1); // 급여 정보 등록 함수
                                    // type 1 : 월 급여 사원, payInfo : 1
                                    // type 2: 일 급여 사원, payInfo : 근무 일수
                                    // type 3 : 영업사원, payInfo : 월 매출액
  void showAllPayCost() const;      // 모든 사원 급여정보 확인 함수
  void showTotalPayCost() const;    // 총 지출해야 할 급여 확인 함수
};
#endif
