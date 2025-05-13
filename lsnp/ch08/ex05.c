#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LOOP_MAX 10
int commonCounter = 0;
void *inc_thread(void *);

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
  return 0;
}

void *inc_thread(void *arg) {
  int loopCount;
  int temp;
  char buffer[80];
  int i;

  for (loopCount = 0; loopCount < LOOP_MAX; loopCount++) {
    sprintf(buffer, "<%s>Common counter : from %d to", (char *)arg,
            commonCounter);
    write(1, buffer, strlen(buffer));
    temp = commonCounter;
    for (i = 0; i < 9000000; i++)
      ;
    commonCounter = temp + 1;
    sprintf(buffer, "%d\n", commonCounter);
    write(1, buffer, strlen(buffer));
    for (i = 0; i < 5000000; i++)
      ;
  }
}
