#include "rpi_server.h"

SharedData shared;

pthread_t led_thread;
pthread_t i2c_thread;

ChildProcess spk = {-1, 0};
ChildProcess seg = {-1, 0};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage : %s port \n", argv[0]);
    exit(1);
  }

  daemonize();
  setup_signals();

  // this will keep getting values from CDS sensor and user input LED value, and
  // update the LED brightness based on the values gathered
  gpio_setup();

  shared_var_init();

  pthread_create(&led_thread, NULL, led_func, &shared);
  pthread_create(&i2c_thread, NULL, i2c_func, &shared);
  atexit(cleanup);

  setup_server(PORT);

  return 0;
}
