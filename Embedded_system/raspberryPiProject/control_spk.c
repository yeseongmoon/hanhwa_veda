#include "control_spk.h"

int notes[] = {391, 391,    440,    440,    391,    391,    329.63, 329.63,
               391, 391,    329.63, 329.63, 293.66, 293.66, 293.66, 0,
               391, 391,    440,    440,    391,    391,    329.63, 329.63,
               391, 329.63, 293.66, 329.63, 261.63, 261.63, 261.63, 0};

void control_spk(int arg) {
  if (arg == 1) {
    softToneCreate(SPKR);
    for (int i = 0; i < TOTAL; ++i) {
      softToneWrite(SPKR, notes[i]);
      delay(280);
    }
    softToneWrite(SPKR, 0);
  } else if (arg == 2) {
    softToneWrite(SPKR, 0);
    softToneStop(SPKR);
    pinMode(SPKR, INPUT);
    delay(200);
  }
}
