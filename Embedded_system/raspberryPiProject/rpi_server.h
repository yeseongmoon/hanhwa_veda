#ifndef __RPI_SERVER_H__
#define __RPI_SERVER_H__

#include <arpa/inet.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <softPwm.h>
#include <softTone.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

enum { LED = 1, CDS, SPK, SEG, EXIT };

#define MAXBUF 1024
#define GPIO18 18
#define GPIO26 26
#define SPKR 25
#define PORT atoi(argv[1])

// for the sake of tracking the states
typedef struct {
  int a2dVal;
  int led_brightness;
  int cds_brightness;
  int pot_brightness;
  int cds_on;
  pthread_mutex_t lock;
} SharedData;

// keep track of the child processes
typedef struct {
  pid_t pid;
  int running;
} ChildProcess;

extern SharedData shared;
extern pthread_t led_thread;
extern pthread_t i2c_thread;

extern ChildProcess spk;
extern ChildProcess seg;

void start_process(ChildProcess *proc, pid_t pid);
void stop_process(ChildProcess *proc);
int is_running(ChildProcess *proc);
void check_child_completion(ChildProcess *proc);
void gpio_setup();
void shared_var_init();
void cleanup();
void setup_signals();
void handle_termination(int signum);
void setup_server(int port);
void server_start(int connfd);
void daemonize();

typedef void (*LED_FUNC)(void *);
typedef void (*SPK_FUNC)(int);
typedef void (*SEG_FUNC)(int);
typedef void (*I2C_FUNC)(void *);

void *led_func(void *arg);
void *i2c_func(void *arg);
void spk_func(int arg);
void seg_func(int arg);

#endif
