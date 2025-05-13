// c11_producer_consumer.c
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define MAX_BUFFER_SIZE 10
#define MAX_THREADS 16

typedef struct {
  int *buffer;
  int count;
  int in;
  int out;
  atomic_int item;
  atomic_int produced;
  atomic_int consumed;
  int buffer_size;
  int items_per_producer;
  int num_producers;
  int num_consumers;
  int delay_mode;

  mtx_t mutex;
  cnd_t not_full;
  cnd_t not_empty;
} shared_buffer_t;

shared_buffer_t shared;

int producer(void *arg) {
  int id = *(int *)arg;
  for (int i = 0; i < shared.items_per_producer; i++) {
    mtx_lock(&shared.mutex);

    while (shared.count == shared.buffer_size)
      cnd_wait(&shared.not_full, &shared.mutex);

    shared.buffer[shared.in] = atomic_fetch_add(&shared.item, 1);
    printf("Producer_%d produced item %d\n", id, shared.buffer[shared.in]);
    shared.in = (shared.in + 1) % shared.buffer_size;
    shared.count++;
    atomic_fetch_add(&shared.produced, 1);

    cnd_signal(&shared.not_empty);
    mtx_unlock(&shared.mutex);

    if (shared.delay_mode == 1)
      thrd_sleep(&(struct timespec){.tv_sec = 0, .tv_nsec = 500000000L}, NULL);
  }
  return 0;
}

int consumer(void *arg) {
  int id = *(int *)arg;
  int items_to_consume =
      (shared.items_per_producer * shared.num_producers) / shared.num_consumers;

  for (int i = 0; i < items_to_consume; i++) {
    mtx_lock(&shared.mutex);

    while (shared.count == 0)
      cnd_wait(&shared.not_empty, &shared.mutex);

    int item = shared.buffer[shared.out];
    shared.out = (shared.out + 1) % shared.buffer_size;
    shared.count--;
    atomic_fetch_add(&shared.consumed, 1);
    printf("Consumer_%d consumed item %d\n", id, item);

    cnd_signal(&shared.not_full);
    mtx_unlock(&shared.mutex);

    if (shared.delay_mode == 0)
      thrd_sleep(&(struct timespec){.tv_sec = 0, .tv_nsec = 500000000L}, NULL);
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 6) {
    fprintf(
        stderr,
        "Usage: %s NUM_PRODUCERS NUM_CONSUMERS ITEMS BUFFER_SIZE DELAY_MODE\n",
        argv[0]);
    return EXIT_FAILURE;
  }

  shared.num_producers = atoi(argv[1]);
  shared.num_consumers = atoi(argv[2]);
  shared.items_per_producer = atoi(argv[3]);
  shared.buffer_size = atoi(argv[4]);
  shared.delay_mode = atoi(argv[5]);

  if (shared.num_consumers >=
      shared.items_per_producer * shared.num_producers) {
    fprintf(stderr, "Consumers must be fewer than total items.\n");
    return EXIT_FAILURE;
  }
  if (shared.buffer_size > MAX_BUFFER_SIZE) {
    fprintf(stderr, "Buffer size must be <= %d.\n", MAX_BUFFER_SIZE);
    return EXIT_FAILURE;
  }
  if (shared.num_producers > MAX_THREADS ||
      shared.num_consumers > MAX_THREADS) {
    fprintf(stderr, "Threads must be <= %d.\n", MAX_THREADS);
    return EXIT_FAILURE;
  }

  shared.buffer = malloc(shared.buffer_size * sizeof(int));
  if (!shared.buffer) {
    perror("malloc");
    return EXIT_FAILURE;
  }

  shared.count = shared.in = shared.out = 0;
  atomic_init(&shared.item, 0);
  atomic_init(&shared.produced, 0);
  atomic_init(&shared.consumed, 0);

  if (mtx_init(&shared.mutex, mtx_plain) != thrd_success ||
      cnd_init(&shared.not_full) != thrd_success ||
      cnd_init(&shared.not_empty) != thrd_success) {
    fprintf(stderr, "Failed to initialize synchronization primitives.\n");
    free(shared.buffer);
    return EXIT_FAILURE;
  }

  thrd_t producers[shared.num_producers], consumers[shared.num_consumers];
  int prod_ids[shared.num_producers], cons_ids[shared.num_consumers];

  for (int i = 0; i < shared.num_producers; i++) {
    prod_ids[i] = i;
    if (thrd_create(&producers[i], producer, &prod_ids[i]) != thrd_success)
      fprintf(stderr, "Failed to create producer thread %d\n", i);
  }

  for (int i = 0; i < shared.num_consumers; i++) {
    cons_ids[i] = i;
    if (thrd_create(&consumers[i], consumer, &cons_ids[i]) != thrd_success)
      fprintf(stderr, "Failed to create consumer thread %d\n", i);
  }

  for (int i = 0; i < shared.num_producers; i++)
    thrd_join(producers[i], NULL);
  for (int i = 0; i < shared.num_consumers; i++)
    thrd_join(consumers[i], NULL);

  free(shared.buffer);
  mtx_destroy(&shared.mutex);
  cnd_destroy(&shared.not_full);
  cnd_destroy(&shared.not_empty);

  return EXIT_SUCCESS;
}
