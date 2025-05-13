#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 10
#define MAX_THREADS 16

typedef struct {
  int *buffer;
  int count;
  int in;
  int out;
  int item;
  int produced;
  int consumed;
  int buffer_size;
  int items_per_producer;
  int num_producers;
  int num_consumers;
  int delay_mode;

  pthread_mutex_t mutex;
  pthread_cond_t not_full;
  pthread_cond_t not_empty;
} shared_buffer_t;

shared_buffer_t shared;

void *producer(void *arg) {
  int id = *(int *)arg;
  for (int i = 0; i < shared.items_per_producer; i++) {
    pthread_mutex_lock(&shared.mutex);

    while (shared.count == shared.buffer_size)
      pthread_cond_wait(&shared.not_full, &shared.mutex);

    shared.buffer[shared.in] = shared.item++;
    printf("Producer_%d produced item %d\n", id, shared.buffer[shared.in]);
    shared.in = (shared.in + 1) % shared.buffer_size;
    shared.count++;
    shared.produced++;

    pthread_cond_signal(&shared.not_empty);
    pthread_mutex_unlock(&shared.mutex);

    if (shared.delay_mode == 1)
      usleep(500000);
  }
  return NULL;
}

void *consumer(void *arg) {
  int id = *(int *)arg;
  int items_to_consume =
      (shared.items_per_producer * shared.num_producers) / shared.num_consumers;

  for (int i = 0; i < items_to_consume; i++) {
    pthread_mutex_lock(&shared.mutex);

    while (shared.count == 0)
      pthread_cond_wait(&shared.not_empty, &shared.mutex);

    int item = shared.buffer[shared.out];
    shared.out = (shared.out + 1) % shared.buffer_size;
    shared.count--;
    shared.consumed++;
    printf("Consumer_%d consumed item %d\n", id, item);

    pthread_cond_signal(&shared.not_full);
    pthread_mutex_unlock(&shared.mutex);

    if (shared.delay_mode == 0)
      usleep(500000);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 6) {
    fprintf(
        stderr,
        "Usage: %s NUM_PRODUCERS NUM_CONSUMERS ITEMS BUFFER_SIZE DELAY_MODE\n",
        argv[0]);
    exit(EXIT_FAILURE);
  }

  shared.num_producers = atoi(argv[1]);
  shared.num_consumers = atoi(argv[2]);
  shared.items_per_producer = atoi(argv[3]);
  shared.buffer_size = atoi(argv[4]);
  shared.delay_mode = atoi(argv[5]);

  if (shared.num_consumers >=
      shared.items_per_producer * shared.num_producers) {
    fprintf(stderr, "Consumers must be fewer than total items.\n");
    exit(EXIT_FAILURE);
  }
  if (shared.buffer_size > MAX_BUFFER_SIZE) {
    fprintf(stderr, "Buffer size must be <= %d.\n", MAX_BUFFER_SIZE);
    exit(EXIT_FAILURE);
  }
  if (shared.num_producers > MAX_THREADS ||
      shared.num_consumers > MAX_THREADS) {
    fprintf(stderr, "Threads must be <= %d.\n", MAX_THREADS);
    exit(EXIT_FAILURE);
  }

  shared.buffer = malloc(shared.buffer_size * sizeof(int));
  if (!shared.buffer) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  shared.count = shared.in = shared.out = shared.item = shared.produced =
      shared.consumed = 0;
  pthread_mutex_init(&shared.mutex, NULL);
  pthread_cond_init(&shared.not_full, NULL);
  pthread_cond_init(&shared.not_empty, NULL);

  pthread_t producers[shared.num_producers], consumers[shared.num_consumers];
  int prod_ids[shared.num_producers], cons_ids[shared.num_consumers];

  for (int i = 0; i < shared.num_producers; i++) {
    prod_ids[i] = i;
    if (pthread_create(&producers[i], NULL, producer, &prod_ids[i]))
      perror("pthread_create producer");
  }

  for (int i = 0; i < shared.num_consumers; i++) {
    cons_ids[i] = i;
    if (pthread_create(&consumers[i], NULL, consumer, &cons_ids[i]))
      perror("pthread_create consumer");
  }

  for (int i = 0; i < shared.num_producers; i++)
    pthread_join(producers[i], NULL);
  for (int i = 0; i < shared.num_consumers; i++)
    pthread_join(consumers[i], NULL);

  free(shared.buffer);
  pthread_mutex_destroy(&shared.mutex);
  pthread_cond_destroy(&shared.not_full);
  pthread_cond_destroy(&shared.not_empty);

  return 0;
}
