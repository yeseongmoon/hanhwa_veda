#include <fcntl.h>
#include <linux/gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define GPIOCHIP "/dev/gpiochip0"

int main(int argc, char *argv[]) {
  int fd, ret;
  struct gpiohandle_request gpio;
  struct gpiohandle_data data;

  if ((fd = open(GPIOCHIP, O_RDWR)) < 0) {
    perror("open");
    exit(1);
  }

  gpio.lineoffsets[0] = 18;
  gpio.lines = 1;
  gpio.flags = GPIOHANDLE_REQUEST_OUTPUT;
  gpio.default_values[0] = 0;

  if ((ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &gpio)) < 0) {
    perror("ioctl");
    exit(1);
  }

  int i = 10, light = 0;
  while (i--) {
    data.values[0] = light;
    if ((ret = ioctl(gpio.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data)) < 0) {
      perror("ioctl");
      close(fd);
      close(gpio.fd);
      exit(1);
    }
    sleep(1);
    light = !light;
    printf("%d\n", light);
  }

  data.values[0] = 0;
  if ((ret = ioctl(gpio.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data)) < 0) {
    perror("ioctl");
    close(fd);
    close(gpio.fd);
    exit(1);
  }

  close(fd);
  close(gpio.fd);
  return 0;
}
