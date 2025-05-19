#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXDATASIZE 100

int main(int argc, char *argv[]) {
  int sockfd;
  char buf[MAXDATASIZE];
  struct hostent *he;
  struct sockaddr_in client_addr;

  if (argc != 2) {
    fprintf(stderr, "usage : client hostname \n");
    exit(1);
  }
  if ((he = gethostbyname(argv[1])) == NULL) {
    perror("gethostbyname");
    exit(1);
  }
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }
  client_addr.sin_family = AF_INET;
  client_addr.sin_port = htons(60000);
  client_addr.sin_addr = *((struct in_addr *)he->h_addr);

  memset(&(client_addr.sin_zero), '\0', 8);
  if (connect(sockfd, (struct sockaddr *)&client_addr,
              sizeof(struct sockaddr)) == -1) {
    perror("connect");
    exit(1);
  }
  char input[10];
  while (1) {
    printf(" ------ MENU ------\n");
    printf(" 1. ON\n 2. OFF\n 3. Play Music\n 4. Read CDS sensor\n 5. EXIT\n");
    printf(" --> ");
    fgets(input, 10, stdin);
    input[strlen(input)] = '\0';
    send(sockfd, input, strlen(input), 0);
    if (strcmp(input, "5\n") == 0) {
      break;
    }
  }
  close(sockfd);
  return 0;
}
