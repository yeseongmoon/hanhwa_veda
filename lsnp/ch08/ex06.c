#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LOOP_MAX 10
int commonCounter = 0;
void *inc_thread(void *);
pthread_mutex_t mutexid = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {
  pthread_t tid1;
  pthread_t tid2;
  if ((pthread_create(&tid1, NULL, inc_thread, "thread1")) ||
      (pthread_create(&tid2, NULL, inc_thread, "thread2"))) {
    perror("pthread_create");
    exit(errno);
  }
  pthread_join(tid1, (void **)NULL);
  pthread_join(tid2, (void **)NULL);

  pthread_mutex_destroy(&mutexid);
  return 0;
}

void *inc_thread(void *arg) {
  int loopCount;
  int temp;
  char buffer[80];
  int i;
  int ret_value;

  for (loopCount = 0; loopCount < LOOP_MAX; loopCount++) {
    if ((ret_value = pthread_mutex_lock(&mutexid)) != 0) {
      perror("pthread_mutex_lock");
      exit(1);
    }
    sprintf(buffer, "<%s>Common counter : from %d to ", (char *)arg,
            commonCounter);
    write(1, buffer, strlen(buffer));
    temp = commonCounter;
    for (i = 0; i < 9000000; i++)
      ;
    commonCounter = temp + 1;
    sprintf(buffer, "%d\n", commonCounter);
    write(1, buffer, strlen(buffer));
    if ((ret_value = pthread_mutex_unlock(&mutexid)) != 0) {
      perror("pthread_mutex_lock");
      exit(1);
    }
    for (i = 0; i < 5000000; i++)
      ;
  }
}
