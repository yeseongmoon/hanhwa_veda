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
  int shmid, semid, i, j;
  char *shmaddr;
  struct sembuf sem;

  if ((shmid = shmget(0x123400, 30, 0600 | IPC_CREAT | IPC_EXCL)) == -1) {
    if ((shmid = shmget(0x123400, 30, 0600)) == -1) {
      perror("shmget");
      exit(1);
    }
  }

  if ((semid = semget(0x45600, 2, 0600 | IPC_CREAT | IPC_EXCL)) == -1) {
    if ((semid = semget(0x45600, 2, 0600)) == -1) {
      perror("semget");
      exit(1);
    }
  }
  if ((shmaddr = shmat(shmid, NULL, 0)) == NULL) {
    perror("shmat");
    exit(1);
  }

  while (1) {
    if (!strcmp(shmaddr, "end"))
      break;
    if (!strcmp(shmaddr, ""))
      continue;
    sem.sem_num = 0;
    sem.sem_op = -1;
    sem.sem_flg = SEM_UNDO;
    if (semop(semid, &sem, 1) == -1) {
      perror("semop");
      exit(1);
    }
    printf("recv: %s\n", shmaddr);
    sem.sem_num = 1;
    sem.sem_op = 1;
    sem.sem_flg = SEM_UNDO;
    if (semop(semid, &sem, 1) == -1) {
      perror("semop");
      exit(1);
    }
    sleep(1);
  }
  if (shmdt(shmaddr) == -1) {
    perror("shmdt");
    exit(1);
  }
  if (shmctl(shmid, IPC_RMID, (struct shmid_ds *)0) == -1) {
    perror("shmctl");
    exit(1);
  }

  semctl(semid, 0, IPC_RMID);

  return 0;
}
