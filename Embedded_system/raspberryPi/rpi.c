#include <pthread.h>
#include <softTone.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define GPIO18 18
#define SPKR 25 /* GPIO25 */
#define TOTAL 32

int notes[] = {391, 391,    440,    440,    391,    391,    329.63, 329.63,
               391, 391,    329.63, 329.63, 293.66, 293.66, 293.66, 0,
               391, 391,    440,    440,    391,    391,    329.63, 329.63,
               391, 329.63, 293.66, 329.63, 261.63, 261.63, 261.63, 0};

void *control_led(void *arg) {
  pinMode(GPIO18, OUTPUT);
  if (strcmp(arg, "ON") == 0) {
    digitalWrite(GPIO18, 1);
    delay(200);
  } else {
    digitalWrite(GPIO18, 0);
    delay(200);
  }
  return NULL;
}

void *musicPlay(void *arg) {
  softToneCreate(SPKR);
  for (int i = 0; i < TOTAL; ++i) {
    softToneWrite(SPKR, notes[i]);
    delay(280);
  }
  softToneWrite(SPKR, 0);
  return NULL;
}

void *startCDS(void *arg) {
  int fd;
  int a2dChannel = 0;
  int prev, a2dVal;
  int threshold = 180;

  if ((fd = wiringPiI2CSetupInterface("/dev/i2c-1", 0x48)) < 0) {
    perror("wiringPiI2CSetupInterface");
    exit(1);
  }

  while (1) {
    wiringPiI2CWrite(fd, 0x00 | a2dChannel);
    prev = wiringPiI2CRead(fd);
    a2dVal = wiringPiI2CRead(fd);
    if (a2dVal < threshold) {
      printf("Bright!\n");
      musicPlay(NULL);
    } else {
      printf("Dark!\n");
    }
    delay(1000);
  }
  return NULL;
}

int main() {
  pthread_t thread, CDS_thread;
  int input;
  if (wiringPiSetupGpio() == -1)
    return -1;

  while (1) {
    printf(" ------ MENU ------\n");
    printf(" 1. ON\n 2. OFF\n 3. Play Music\n 4. Read CDS sensor\n 5. EXIT\n");
    printf(" --> ");
    scanf("%d", &input);
    if (input == 1) {
      if (pthread_create(&thread, NULL, control_led, "ON") != 0) {
        perror("pthread_create");
        exit(1);
      }
      pthread_join(thread, NULL);
    } else if (input == 2) {
      if (pthread_create(&thread, NULL, control_led, "OFF") != 0) {
        perror("pthread_create");
        exit(1);
      }
      pthread_join(thread, NULL);
    } else if (input == 3) {
      if (pthread_create(&thread, NULL, musicPlay, NULL) != 0) {
        perror("pthread_create");
        exit(1);
      }
      pthread_join(thread, NULL);
    } else if (input == 4) {
      if (pthread_create(&CDS_thread, NULL, startCDS, NULL) != 0) {
        perror("pthread_create");
        exit(1);
      }

      pthread_join(CDS_thread, NULL);
    } else if (input == 5) {
      break;
    }
  }
  digitalWrite(GPIO18, 0);
  return 0;
}
