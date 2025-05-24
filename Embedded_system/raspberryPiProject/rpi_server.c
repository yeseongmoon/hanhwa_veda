#include "rpi_server.h"

// helper functions for managing processes
void start_process(ChildProcess *proc, pid_t pid) {
  proc->pid = pid;
  proc->running = 1;
}

void stop_process(ChildProcess *proc) {
  if (proc->pid > 0) {
    kill(proc->pid, SIGTERM);
    waitpid(proc->pid, NULL, 0);
  }
  proc->pid = -1;
  proc->running = 0;
}

int is_running(ChildProcess *proc) { return proc->running; }

void check_child_completion(ChildProcess *proc) {
  if (proc->pid > 0) {
    int status;
    pid_t result = waitpid(proc->pid, &status, WNOHANG);
    if (result == proc->pid) {
      proc->pid = -1;
      proc->running = 0;
    }
  }
}

typedef void (*LED_FUNC)(void *);
void *led_func(void *arg) {
  LED_FUNC ledfunc;

  const char *home = getenv("HOME");
  if (!home) {
    perror("getenv");
    exit(1);
  }

  char fullpath[BUFSIZ];
  snprintf(fullpath, sizeof(fullpath), "%s/%s", home, "libled.so");

  void *handle = dlopen(fullpath, RTLD_LAZY);
  if (handle == NULL) {
    perror("dlopen");
    exit(1);
  }

  ledfunc = (LED_FUNC)dlsym(handle, "control_led");
  SharedData *shared = (SharedData *)arg;
  ledfunc(shared);
  dlclose(handle);
  return NULL;
}

typedef void (*I2C_FUNC)(void *);
void *i2c_func(void *arg) {
  I2C_FUNC i2cfunc;

  const char *home = getenv("HOME");
  if (!home) {
    perror("getenv");
    exit(1);
  }

  char fullpath[BUFSIZ];
  snprintf(fullpath, sizeof(fullpath), "%s/%s", home, "libi2c.so");

  void *handle = dlopen(fullpath, RTLD_LAZY);
  if (handle == NULL) {
    perror("dlopen");
    exit(1);
  }

  i2cfunc = (LED_FUNC)dlsym(handle, "control_i2c");
  SharedData *shared = (SharedData *)arg;
  i2cfunc(shared);
  dlclose(handle);
  return NULL;
}

typedef void (*SPK_FUNC)(int);
void spk_func(int arg) {
  SPK_FUNC spkfunc;

  const char *home = getenv("HOME");
  if (!home) {
    perror("getenv");
    exit(1);
  }

  char fullpath[BUFSIZ];
  snprintf(fullpath, sizeof(fullpath), "%s/%s", home, "libspk.so");

  void *handle = dlopen(fullpath, RTLD_LAZY);
  if (handle == NULL) {
    perror("dlopen");
    exit(1);
  }

  spkfunc = (SPK_FUNC)dlsym(handle, "control_spk");
  spkfunc(arg);
  dlclose(handle);
}

typedef void (*SEG_FUNC)(int);
void seg_func(int arg) {
  SEG_FUNC segfunc;

  const char *home = getenv("HOME");
  if (!home) {
    perror("getenv");
    exit(1);
  }

  char fullpath[BUFSIZ];
  snprintf(fullpath, sizeof(fullpath), "%s/%s", home, "libseg.so");

  void *handle = dlopen(fullpath, RTLD_LAZY);
  if (handle == NULL) {
    perror("dlopen");
    exit(1);
  }

  segfunc = (SEG_FUNC)dlsym(handle, "control_seg");
  segfunc(arg);
  dlclose(handle);
}

void gpio_setup() {
  if (wiringPiSetupGpio() == -1)
    exit(1);

  pinMode(GPIO18, OUTPUT);
  pinMode(GPIO26, OUTPUT);
}

// this is for the CDS censor & LED control
void shared_var_init() {
  shared.a2dVal = 0;
  shared.led_brightness = 0;
  shared.cds_brightness = 0;
  shared.pot_brightness = 0;
  shared.cds_on = 0;
  pthread_mutex_init(&shared.lock, NULL);
}

void cleanup() {
  printf("\n[EXIT] Cleaning up...\n");

  stop_process(&seg);
  stop_process(&spk);

  // clean up thread
  pthread_cancel(led_thread);
  pthread_join(led_thread, NULL);

  pthread_cancel(i2c_thread);
  pthread_join(i2c_thread, NULL);

  softPwmWrite(GPIO18, 0);
  softPwmWrite(GPIO26, 0);
  pinMode(GPIO18, INPUT);
  pinMode(GPIO26, INPUT);
  softToneWrite(SPKR, 0);
  softToneStop(SPKR);
  pinMode(SPKR, INPUT);

  printf("[EXIT] Cleanup done.\n");
}

void setup_signals() {
  sigset_t mask;
  sigfillset(&mask);
  sigdelset(&mask, SIGINT);
  sigdelset(&mask, SIGTERM);
  sigprocmask(SIG_SETMASK, &mask, NULL);
  signal(SIGINT, handle_termination);
  signal(SIGTERM, handle_termination);
  signal(SIGPIPE, SIG_IGN);
}

void handle_termination(int signum) {
  printf("\n[SIGINT] Interupt Received\n");
  cleanup();
  exit(0);
}

void setup_server(int port) {
  int sockfd, connfd;
  socklen_t len;
  struct sockaddr_in servaddr, cli;

  // socket create and verification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    exit(0);
  }

  printf("Socket successfully created..\n");
  bzero(&servaddr, sizeof(servaddr));

  int optval = 1;

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) ==
      -1) {
    perror("setsockopt");
    exit(1);
  }

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
    printf("socket bind failed...\n");
    exit(0);
  }
  printf("Socket successfully binded..\n");

  // Now server is ready to listen and verification
  if ((listen(sockfd, 5)) != 0) {
    printf("Listen failed...\n");
    exit(0);
  }
  printf("Server listening..\n");
  len = sizeof(cli);

  while (1) {
    int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
    if (connfd < 0) {
      perror("accept");
      continue;
    }
    printf("Client connected!\n");

    server_start(connfd);
    close(connfd);
    printf("Client disconnected ....\n");
  }
  close(sockfd);
}

void server_start(int connfd) {
  int user_input;
  char buffer[MAXBUF];
  ssize_t recv_len;
  while (1) {
    snprintf(buffer, sizeof(buffer),
             " ====== MENU ======\n 1. LED\n 2. CDS\n 3. SPEAKER\n 4. 7 "
             "SEGMENT\n 5. EXIT\n --> ");
    send(connfd, buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));

    if ((recv_len = recv(connfd, buffer, sizeof(buffer) - 1, 0)) <= 0) {
      perror("recv");
      break;
    }
    buffer[recv_len] = '\0';
    sscanf(buffer, "%d", &user_input);
    memset(buffer, 0, sizeof(buffer));

    if (user_input == '\n') {
      continue;
    }
    if (user_input == LED) {
      int cmd;
      while (1) {
        snprintf(buffer, sizeof(buffer),
                 " ------ CONTROL COMMAND ------\n 1. LED ON\n 2. LED OFF\n 3. "
                 "Enter the Brightness\n 4. BACK TO MENU\n --> ");
        send(connfd, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));

        if ((recv_len = recv(connfd, buffer, sizeof(buffer) - 1, 0)) <= 0) {
          perror("recv");
          break;
        }
        buffer[recv_len] = '\0';
        sscanf(buffer, "%d", &cmd);
        if (cmd == '\n') {
          continue;
        }

        memset(buffer, 0, sizeof(buffer));
        if (cmd == 1) {
          shared.led_brightness = 100;
        } else if (cmd == 2) {
          shared.led_brightness = 0;
        } else if (cmd == 3) {
          int value;
          send(connfd, "[LED] value(0-100) --> ", 23, 0);
          if ((recv_len = recv(connfd, buffer, sizeof(buffer) - 1, 0)) <= 0) {
            perror("recv");
            break;
          }
          buffer[recv_len] = '\0';
          sscanf(buffer, "%d", &value);
          if (value == '\n') {
            continue;
          }
          memset(buffer, 0, sizeof(buffer));
          shared.led_brightness = value;
        } else if (cmd == 4) {
          break;
        } else {
          send(connfd, "Invalid command!\n", 19, 0);
        }
      }
    }

    if (user_input == CDS) {
      int cmd;

      while (1) {
        snprintf(buffer, sizeof(buffer),
                 " ------ CONTROL COMMAND ------\n 1. Current CDS Value\n 2. "
                 "CDS Start\n 3. CDS Stop\n 4. BACK TO MENU\n --> ");
        send(connfd, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));

        if ((recv_len = recv(connfd, buffer, sizeof(buffer) - 1, 0)) <= 0) {
          perror("recv");
          break;
        }
        buffer[recv_len] = '\0';
        sscanf(buffer, "%d", &cmd);
        if (cmd == '\n') {
          continue;
        }
        memset(buffer, 0, sizeof(buffer));

        if (cmd == 1 && shared.cds_on == 1) {
          snprintf(buffer, sizeof(buffer), "[CDS] Current Value: %d\n",
                   shared.a2dVal);
          send(connfd, buffer, strlen(buffer), 0);
          memset(buffer, 0, sizeof(buffer));
        } else if (cmd == 2 && shared.cds_on == 0) {
          shared.cds_on = 1;
        } else if (cmd == 3 && shared.cds_on == 1) {
          shared.cds_on = 0;
        } else if (cmd == 4) {
          break;
        } else {
          send(connfd, "[CDS] not running ... or Invalid command\n", 43, 0);
        }
      }
    }

    if (user_input == SPK) {
      int cmd;
      while (1) {
        check_child_completion(&spk);
        check_child_completion(&seg);

        snprintf(buffer, sizeof(buffer),
                 " ------ CONTROL COMMAND ------\n 1. Music ON\n 2. Music "
                 "OFF\n 3. BACK TO MENU\n --> ");
        send(connfd, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));

        if ((recv_len = recv(connfd, buffer, sizeof(buffer) - 1, 0)) <= 0) {
          perror("recv");
          break;
        }
        buffer[recv_len] = '\0';
        sscanf(buffer, "%d", &cmd);
        if (cmd == '\n') {
          continue;
        }
        memset(buffer, 0, sizeof(buffer));

        if (cmd == 1 && !is_running(&spk) && !is_running(&seg)) {
          send(connfd, "[Music] on ... \n", 18, 0);
          pid_t pid = fork();
          if (pid == -1) {
            perror("fork");
            exit(1);
          } else if (pid == 0) {
            spk_func(cmd);
            exit(0);
          }
          start_process(&spk, pid);
        } else if (cmd == 2 && is_running(&spk)) {
          send(connfd, "[Music] off ... \n", 19, 0);
          spk_func(cmd);
          stop_process(&spk);
          delay(200);
        } else if (cmd == 3) {
          break;
        } else if (is_running(&spk)) {
          send(connfd, "[SPK] already being played! Please wait!\n", 43, 0);
        } else if (is_running(&seg)) {
          send(connfd, "[SEG] already running! Please wait!\n", 38, 0);
        } else {
          send(connfd, "Invalid command!\n", 19, 0);
        }
      }
    }

    if (user_input == SEG) {
      int cmd;
      while (1) {
        check_child_completion(&spk);
        check_child_completion(&seg);

        snprintf(buffer, sizeof(buffer),
                 " ------ CONTROL COMMAND ------\n 1. Alarm Start\n 2. BACK TO "
                 "MENU\n --> ");
        send(connfd, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));

        if ((recv_len = recv(connfd, buffer, sizeof(buffer) - 1, 0)) <= 0) {
          perror("recv");
          break;
        }
        buffer[recv_len] = '\0';
        sscanf(buffer, "%d", &cmd);
        if (cmd == '\n') {
          continue;
        }
        memset(buffer, 0, sizeof(buffer));

        if (cmd == 1 && !is_running(&seg) && !is_running(&spk)) {
          int value;
          send(connfd, "Enter a number(0-9) --> ", 24, 0);
          if ((recv_len = recv(connfd, buffer, sizeof(buffer) - 1, 0)) <= 0) {
            perror("recv");
            break;
          }
          buffer[recv_len] = '\0';
          sscanf(buffer, "%d", &value);
          if (value == '\n') {
            continue;
          }
          memset(buffer, 0, sizeof(buffer));
          if (value > 9 || value < 0) {
            send(connfd, "Invalid command!\n", 19, 0);
          } else {
            pid_t pid = fork();
            if (pid == -1) {
              perror("fork");
              exit(1);
            } else if (pid == 0) {
              seg_func(value);
              exit(0);
            }
            start_process(&seg, pid);
          }
        } else if (cmd == 2) {
          break;
        } else if (is_running(&seg)) {
          send(connfd, "[SEG] already running! Please wait!\n", 38, 0);
        } else if (is_running(&spk)) {
          send(connfd, "[SPK] already being played! Please wait!\n", 43, 0);
        } else {
          send(connfd, "Invalid command!\n", 19, 0);
        }
      }
    }

    if (user_input == EXIT) {
      send(connfd, "\n ... Exiting ... \n", 21, 0);
      stop_process(&spk);
      stop_process(&seg);
      shared_var_init();
      break;
    }

    while (waitpid(-1, NULL, WNOHANG) > 0)
      ;
  }
}

void daemonize() {
  struct sigaction sa;
  struct rlimit rl;
  pid_t pid;
  int fd0, fd1, fd2;

  umask(0);

  if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
    perror("getrlimit");
    exit(1);
  }

  pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(1);
  }
  if (pid > 0) {
    exit(0);
  }

  if (setsid() < 0) {
    perror("setsid");
    exit(1);
  }

  sa.sa_handler = SIG_IGN;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction(SIGHUP, &sa, NULL) < 0) {
    perror("sigaction");
    exit(1);
  }

  if (chdir("/") < 0) {
    perror("chdir");
    exit(1);
  }

  if (rl.rlim_max == RLIM_INFINITY)
    rl.rlim_max = 1024;
  for (int i = 0; i < rl.rlim_max; i++)
    close(i);

  fd0 = open("/dev/null", O_RDWR);
  fd1 = dup(0);
  fd2 = dup(0);
}
