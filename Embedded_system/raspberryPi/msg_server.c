#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // TODO: learn how to connect server with multiple clients with different port
  // and ip addresses
  int sockfd1, sockfd2, client_len;
  FILE *fp;
  sockfd1 = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd1 == -1) {
    perror("socket");
    exit(1);
  }
  sockfd2 = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd2 == -1) {
    perror("socket");
    exit(1);
  }

  int optval = 1;

  if (setsockopt(sockfd1, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) ==
      -1) {
    perror("setsockopt");
    exit(1);
  }
  if (setsockopt(sockfd2, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) ==
      -1) {
    perror("setsockopt");
    exit(1);
  }

  struct sockaddr_in server1_addr, client_addr, myaddr;
  server1_addr.sin_family = AF_INET;
  server1_addr.sin_port = htons(60000);
  server1_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  memset(&(server1_addr.sin_zero), '\0', 8);

  struct sockaddr_in server2_addr;
  server2_addr.sin_family = AF_INET;
  server2_addr.sin_port = htons(60001);
  server2_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  memset(&(server2_addr.sin_zero), '\0', 8);

  if (bind(sockfd1, (struct sockaddr *)&server1_addr,
           sizeof(struct sockaddr)) == -1) {
    perror("bind");
    exit(1);
  }

  if (bind(sockfd2, (struct sockaddr *)&server2_addr,
           sizeof(struct sockaddr)) == -1) {
    perror("bind");
    exit(1);
  }

  char buf[1024];
  memset(buf, '\0', 1024);
  socklen_t addr_len;
  int n1 = recvfrom(sockfd1, buf, sizeof(buf), 0,
                    (struct sockaddr *)&client_addr, &addr_len);
  buf[n1] = '\0';
  // do something
  getpeername(sockfd1, (struct sockaddr *)&myaddr, &client_len);
  printf("From client1: %s\n", buf);
  printf("client address   :%s\n", inet_ntoa(myaddr.sin_addr));

  memset(buf, '\0', 1024);
  int n2 = recvfrom(sockfd2, buf, sizeof(buf), 0,
                    (struct sockaddr *)&client_addr, &addr_len);
  buf[n2] = '\0';
  getpeername(sockfd2, (struct sockaddr *)&myaddr, &client_len);
  printf("From client2: %s\n", buf);
  printf("client address   :%s\n", inet_ntoa(myaddr.sin_addr));

  close(sockfd1);
  close(sockfd2);
  return 0;
}
