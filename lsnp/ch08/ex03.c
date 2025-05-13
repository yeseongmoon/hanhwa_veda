#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_function(void *args);

int main(int argc, char *argv[]) {
  int status;
  pthread_t a_thread;
  void *thread_result;

  status = pthread_create(&a_thread, NULL, thread_function, (void *)NULL);
  if (status != 0) {
    perror("pthread_create");
    exit(1);
  }
  pthread_detach(a_thread);
  pause();
  // pthread_join(a_thread, &thread_result);
  // printf("%s\n", (char *)thread_result);
  return 0;
}

void *thread_function(void *args) {
  printf("my thread id : %d\n", (int)pthread_self());
  sleep(5);
  pthread_exit("Hello, thread");
}
