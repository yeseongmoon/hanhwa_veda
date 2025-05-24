#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

typedef struct {
  int a2dVal;
  int led_brightness;
  int cds_brightness;
  int pot_brightness;
  int cds_on;
  pthread_mutex_t lock;
} SharedData;

void control_pot(void *arg);
