#include <fcntl.h>
#include <pthread.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <wiringPi.h>

#define GPIO18 18
#define GPIO26 26

typedef struct {
  int a2dVal;
  int led_brightness;
  int cds_brightness;
  int pot_brightness;
  int cds_on;
  pthread_mutex_t lock;
} SharedData;

void control_led(void *);
