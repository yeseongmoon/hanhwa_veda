#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXBUF 1024
#define PORT atoi(argv[2])
int sockfd;

void sigint_handler(int signum) {
  printf("\n[Client] SIGINT received. Closing connection and exiting...\n");

  if (sockfd != -1) {
    close(sockfd);
    printf("[Client] Socket closed.\n");
  }

  exit(0);
}

int main(int argc, char *argv[]) {
  sigset_t mask;
  sigfillset(&mask);
  sigdelset(&mask, SIGINT);
  sigprocmask(SIG_SETMASK, &mask, NULL);
  signal(SIGINT, sigint_handler);

  struct hostent *he;
  struct sockaddr_in client_addr;

  if (argc != 3) {
    fprintf(stderr, "Usage : %s hostname port \n", argv[0]);
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
  memset(&client_addr, 0, sizeof(client_addr));
  client_addr.sin_family = AF_INET;
  client_addr.sin_port = htons(PORT);

  // Try to convert input as IP address
  if (inet_pton(AF_INET, argv[1], &client_addr.sin_addr) <= 0) {
    // Not an IP — try hostname
    struct hostent *he = gethostbyname(argv[1]);
    if (he == NULL) {
      perror("gethostbyname");
      exit(1);
    }
    client_addr.sin_addr = *((struct in_addr *)he->h_addr);
  }

  memset(&(client_addr.sin_zero), '\0', 8);
  if (connect(sockfd, (struct sockaddr *)&client_addr,
              sizeof(struct sockaddr)) == -1) {
    perror("connect");
    exit(1);
  }
  char buffer[MAXBUF];
  while (1) {
    memset(buffer, 0, sizeof(buffer));
    if (recv(sockfd, buffer, sizeof(buffer) - 1, 0) <= 0) {
      printf("Server closed connection.\n");
      break;
    }
    printf("%s", buffer);

    if (strstr(buffer, "-->") != NULL) {
      // Get user input and send
      memset(buffer, 0, sizeof(buffer));
      if (!fgets(buffer, sizeof(buffer), stdin)) {
        break;
      }
      // Remove newline
      buffer[strcspn(buffer, "\n")] = '\0';
      send(sockfd, buffer, strlen(buffer), 0);
    }
  }
  close(sockfd);
  return 0;
}
