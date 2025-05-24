#include <softTone.h>
#include <unistd.h>
#include <wiringPi.h>

#define SPKR 25 /* GPIO25 */
#define TOTAL 32

void display_digit(int);
void control_seg(int);
