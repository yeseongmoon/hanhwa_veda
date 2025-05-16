#include "control_led.h"
#include <wiringPi.h>

#define GPIO18 18

void control_led(int arg) {
  pinMode(GPIO18, OUTPUT);
  if (arg == 1) {
    digitalWrite(GPIO18, 1);
    delay(200);
  } else {
    digitalWrite(GPIO18, 0);
    delay(200);
  }
}
