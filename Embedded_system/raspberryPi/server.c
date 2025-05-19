#include <arpa/inet.h>
#include <dlfcn.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <softTone.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define GPIO18 18
#define SPKR 25 /* GPIO25 */
#define TOTAL 32
#define BACKLOG 10

int notes[] = {391, 391,    440,    440,    391,    391,    329.63, 329.63,
               391, 391,    329.63, 329.63, 293.66, 293.66, 293.66, 0,
               391, 391,    440,    440,    391,    391,    329.63, 329.63,
               391, 329.63, 293.66, 329.63, 261.63, 261.63, 261.63, 0};

typedef void (*FUNC)(int);
void *led_thread(void *arg) {
  int input = *(int *)arg;
  FUNC ledfunc;
  void *handle = dlopen("/home/veda/libled.so", RTLD_LAZY);
  if (handle == NULL) {
    perror("dlopen");
    exit(1);
  }
  ledfunc = (FUNC)dlsym(handle, "control_led");
  ledfunc(input);
  dlclose(handle);
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
  int closed = 0;
  if (wiringPiSetupGpio() == -1)
    return -1;

  int sockfd, new_fd;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  int sin_size;

  // 1. 소켓 생성
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  // 2. 서버 주소 설정
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(60000);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  memset(&(server_addr.sin_zero), '\0', 8);

  // 3. 바인드
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) ==
      -1) {
    perror("bind");
    exit(1);
  }

  // 4. 연결 대기 (listen)
  if (listen(sockfd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  }

  pid_t childpid;
  // 5. 연결 수락 및 처리 루프
  while (1) {
    if (closed == 1)
      break;
    sin_size = sizeof(struct sockaddr_in);
    new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
    if (new_fd == -1) {
      perror("accept");
      continue;
    }

    if ((childpid = fork()) == 0) {

      char receive[10] = {'\0'};
      int input;

      while (1) {
        ssize_t recv_size = recv(new_fd, receive, sizeof(receive) - 1, 0);
        if (recv_size <= 0) {
          perror("recv");
          break;
        }
        receive[recv_size] = '\0';
        if (recv_size == 0 || strlen(receive) == 0) {
          continue; // skip empty messages
        }

        input = atoi(receive);
        printf("Received: %d\n", input);

        pthread_t thread;
        if (input == 1 || input == 2) {
          int *arg = malloc(sizeof(int));
          *arg = input;
          if (pthread_create(&thread, NULL, led_thread, arg) != 0) {
            perror("pthread_create");
            break;
          }
          pthread_join(thread, NULL);
        } else if (input == 3) {
          if (pthread_create(&thread, NULL, musicPlay, NULL) != 0) {
            perror("pthread_create");
            break;
          }
          pthread_join(thread, NULL);
        } else if (input == 4) {
          pthread_t cds_thread;
          if (pthread_create(&cds_thread, NULL, startCDS, NULL) != 0) {
            perror("pthread_create");
            break;
          }
          pthread_join(thread, NULL);
        } else if (input == 5) {
          closed = 1;
          break;
        }
        memset(receive, 0, sizeof(receive));
      }

      close(sockfd);
      close(new_fd);
      while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
      exit(0);
    }
  }
  close(sockfd);
  close(new_fd);
  digitalWrite(GPIO18, 0);
  return 0;
}
