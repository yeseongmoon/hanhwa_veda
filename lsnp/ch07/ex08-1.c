#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main() {
  int semid, i, j;
  char *semaddr;
  struct sembuf sem = {0, -1, SEM_UNDO};

  if ((semid = semget(0x123400, 30, 0600 | IPC_CREAT | IPC_EXCL)) == -1) {
    if ((semid = semget(0x123400, 30, 0600)) == -1) {
      perror("shmget");
      exit(1);
    }
  }

  for (i = 0; i < 20; i++) {
    if (semop(semid, &sem, 1) == -1) {
      perror("semop");
      exit(1);
    }
    printf("send: %d\n", sem.sem_num);
    sleep(3);
  }
  sprintf(semaddr, "end");
  // if (shmdt(semaddr) == -1) {
  //   perror("shmdt");
  //   exit(1);
  // }

  return 0;
}
