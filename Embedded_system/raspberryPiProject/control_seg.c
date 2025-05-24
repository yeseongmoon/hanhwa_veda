#include "control_seg.h"
#include <signal.h>

int seg_pins[4] = {23, 17, 15,
                   14}; /* A : GPIO23, B : GPIO17, C : GPIO, D : GPIO14 */
int notes[] = {800, 0, 800, 0};

const int digits[10][4] = {
    {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 1, 0, 0},
    {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1}, {1, 0, 0, 0}, {1, 0, 0, 1}};

void sigterm_handler(int signum) {
  for (int i = 0; i < 4; i++) {
    pinMode(seg_pins[i], INPUT);
  }
  pinMode(SPKR, INPUT);
}

void display_digit(int digit) {
  for (int i = 0; i < 4; ++i) {
    digitalWrite(seg_pins[i], digits[digit][i]);
  }
}

void control_seg(int arg) {
  signal(SIGTERM, sigterm_handler);

  for (int i = 0; i < 4; i++) {
    pinMode(seg_pins[i], OUTPUT);
    digitalWrite(seg_pins[i], 1);
  }
  while (arg >= 0) {
    display_digit(arg);
    sleep(1);
    arg--;
  }

  softToneCreate(SPKR);
  for (int i = 0; i < 4; ++i) {
    softToneWrite(SPKR, notes[i]);
    delay(280);
  }
  softToneWrite(SPKR, 0);
  softToneStop(SPKR);
  pinMode(SPKR, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(seg_pins[i], INPUT);
  }
}
