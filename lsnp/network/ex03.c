#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int server_sockfd, client_sockfd;
  int state, client_len;

  struct sockaddr_in clientaddr, serveraddr, myaddr;

  // internet 기반의 스트림 소켓을 만들도록 한다.
  if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket error : ");
    exit(0);
  }
  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(50000);

  state =
      bind(server_sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  if (state == -1) {
    perror("bind error : ");
    exit(0);
  }

  state = listen(server_sockfd, 5);
  if (state == -1) {
    perror("listen error : ");
    exit(0);
  }

  client_len = sizeof(struct sockaddr);
  client_sockfd =
      accept(server_sockfd, (struct sockaddr *)&clientaddr, &client_len);

  // client_sockfd = accept(server_sockfd, NULL, NULL);
  if (client_sockfd == -1) {
    perror("Accept error : ");
    exit(0);
  }

  getsockname(client_sockfd, (struct sockaddr *)&myaddr, &client_len);

  printf("local Port      :%d\n", ntohs(myaddr.sin_port));
  printf("local address   :%s\n", inet_ntoa(myaddr.sin_addr));

  getpeername(client_sockfd, (struct sockaddr *)&myaddr, &client_len);

  printf("client Port      :%d\n", myaddr.sin_port);
  printf("client address   :%s\n", inet_ntoa(myaddr.sin_addr));

  close(client_sockfd);
  return 1;
}
