#include <signal.h>
#include <softTone.h>
#include <stdlib.h>
#include <wiringPi.h>

#define SPKR 25 /* GPIO25 */
#define TOTAL 32

void control_spk(int);
