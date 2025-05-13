#include <wiringPi.h>
#define GPIO18 18

int main() {
  int i;
  if (wiringPiSetupGpio() == -1)
    return -1;
  pinMode(GPIO18, OUTPUT);
  for (int i = 0; i < 10; i++) {
    digitalWrite(GPIO18, 0);
    delay(850);
    digitalWrite(GPIO18, 1);
    delay(150);
  }
  digitalWrite(GPIO18, 0);
  return 0;
}
