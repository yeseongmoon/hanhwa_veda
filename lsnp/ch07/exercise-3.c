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

  if ((shmid = shmget(0x123400, 30, 0660 | IPC_CREAT | IPC_EXCL)) == -1) {
    if ((shmid = shmget(0x123400, 30, 0660)) == -1) {
      perror("shmget");
      exit(1);
    }
  }

  if ((semid = semget(0x45600, 2, 0660 | IPC_CREAT | IPC_EXCL)) == -1) {
    if ((semid = semget(0x45600, 2, 0600)) == -1) {
      perror("semget");
      exit(1);
    }
  }

  if ((shmaddr = shmat(shmid, (char *)0, 0)) == NULL) {
    perror("shmat");
    exit(1);
  }

  semctl(semid, 0, SETVAL, 0);
  semctl(semid, 1, SETVAL, 1);

  for (i = 0; i < 20; i++) {
    sem.sem_num = 1;
    sem.sem_op = -1;
    sem.sem_flg = SEM_UNDO;
    if (semop(semid, &sem, 1) == -1) {
      perror("semop");
      exit(1);
    }

    sprintf(shmaddr, "shared memory test %d", i + 1);
    printf("send : %s\n", shmaddr);
    sem.sem_num = 0;
    sem.sem_op = 1;
    sem.sem_flg = SEM_UNDO;

    if (semop(semid, &sem, 1) == -1) {
      perror("semop");
      exit(1);
    }
    sleep(3);
  }

  sem.sem_num = 1;
  sem.sem_op = -1;
  sem.sem_flg = 0;
  semop(semid, &sem, 1);
  sprintf(shmaddr, "end");
  if (shmdt(shmaddr) == -1) {
    perror("shmdt");
    exit(1);
  }
  sem.sem_num = 0;
  sem.sem_op = 1;
  semop(semid, &sem, 1);
  return 0;
}
