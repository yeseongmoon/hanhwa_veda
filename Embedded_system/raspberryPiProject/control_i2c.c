#include "control_i2c.h"

void control_i2c(void *arg) {
  int fd = wiringPiI2CSetupInterface("/dev/i2c-1", 0x48);
  if (fd < 0)
    exit(1);

  SharedData *shared = (SharedData *)arg;
  while (1) {
    pthread_testcancel();
    wiringPiI2CWrite(fd, 0x00); // AIN0
    wiringPiI2CRead(fd);
    shared->a2dVal = wiringPiI2CRead(fd);

    if (shared->cds_on == 1) {
      pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
      pthread_mutex_lock(&shared->lock);
      shared->cds_brightness = (shared->a2dVal > 180) ? 100 : 0;
      pthread_mutex_unlock(&shared->lock);
      pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    } else {
      pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
      pthread_mutex_lock(&shared->lock);
      shared->cds_brightness = 0;
      pthread_mutex_unlock(&shared->lock);
      pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    }

    wiringPiI2CWrite(fd, 0x03); // AIN3
    wiringPiI2CRead(fd);

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    pthread_mutex_lock(&shared->lock);
    shared->pot_brightness = wiringPiI2CRead(fd);
    pthread_mutex_unlock(&shared->lock);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    delay(500);
  }
}
