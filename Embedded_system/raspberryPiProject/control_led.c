#include "control_led.h"

int shm_fd;

void control_led(void *arg) {
  static int softPwmInitialized = 0;

  if (!softPwmInitialized) {
    softPwmCreate(GPIO18, 0, 100);
    softPwmCreate(GPIO26, 0, 255);
    softPwmInitialized = 1;
  }

  SharedData *shared = (SharedData *)arg;

  while (1) {
    pthread_testcancel();

    if (shared != NULL) {
      pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
      pthread_mutex_lock(&shared->lock);

      int brightness =
          shared->cds_on ? shared->cds_brightness : shared->led_brightness;
      softPwmWrite(GPIO18, brightness);
      softPwmWrite(GPIO26, shared->pot_brightness);

      pthread_mutex_unlock(&shared->lock);
      pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    }
    delay(100);
  }
}
