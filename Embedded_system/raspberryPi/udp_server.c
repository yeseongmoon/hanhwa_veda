#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int sockfd;
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("socket");
    exit(1);
  }
  struct sockaddr_in server_addr, client_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(60000);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  memset(&(server_addr.sin_zero), '\0', 8);
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) ==
      -1) {
    perror("bind");
    exit(1);
  }
  char buf[1024];
  socklen_t addr_len;
  while (1) {
    int n = recvfrom(sockfd, buf, sizeof(buf), 0,
                     (struct sockaddr *)&client_addr, &addr_len);
    buf[n] = '\0';
    printf("From client: %s", buf);
  }
  close(sockfd);
  return 0;
}
