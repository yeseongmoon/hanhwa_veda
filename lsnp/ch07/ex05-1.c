#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  int msgid, n;
  char buf[1024];
  struct mymsgbuf {
    long m_type;
    char m_str[1024];
  } sendbuf, recvbuf;

  if ((msgid = msgget(0x123400, IPC_CREAT | 0666)) == -1) {
    perror("msgget");
    exit(1);
  }

  while (1) {
    printf(" User1 --> ");
    fgets(buf, 1023, stdin);
    sendbuf.m_type = 1;
    strcpy(sendbuf.m_str, buf);
    msgsnd(msgid, &sendbuf, strlen(sendbuf.m_str), 0);
    if (!strncmp(buf, "end", 3))
      break;
    n = msgrcv(msgid, &recvbuf, 1024, 2, 0);
    recvbuf.m_str[n] = '\0';
    printf(">> %s\n", recvbuf.m_str);
    if (!strncmp(recvbuf.m_str, "end", 3))
      break;
  }
  sleep(1);
  return 0;
}
