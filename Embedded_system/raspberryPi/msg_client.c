#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define HOSTNAME argv[1]
#define PORT atoi(argv[2])

int main(int argc, char *argv[]) {
  int sockfd;
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("socket");
    exit(1);
  }
  struct sockaddr_in server_addr;
  struct hostent *host;
  if ((host = gethostbyname(HOSTNAME)) == NULL) {
    perror("gethostbyname");
    exit(0);
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  // TODO: this should be fixed. I think the ip address that I'm sending is not
  // right
  server_addr.sin_addr = *(struct in_addr *)host->h_addr;

  memset(&(server_addr.sin_zero), '\0', 8);
  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("connect");
    exit(0);
  }

  printf("\"%s\" message was sent to the server!\n", argv[3]);
  sendto(sockfd, argv[3], sizeof(argv[3]), 0, (struct sockaddr *)&server_addr,
         sizeof(server_addr));

  return 0;
}
