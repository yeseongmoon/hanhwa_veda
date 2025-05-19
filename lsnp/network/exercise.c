#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define BACKLOG 10

int main(void)
{
    int sockfd, new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sin_size;

    // 1. 소켓 생성
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // 2. 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(60000);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&(server_addr.sin_zero), '\0', 8);

    // 3. 바인드
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    // 4. 연결 대기 (listen)
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    // 5. 연결 수락 및 처리 루프
    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        printf("Server : got connection from %s\n", inet_ntoa(client_addr.sin_addr));

        if (!fork()) {
            // 자식 프로세스
            close(sockfd);
            if (send(new_fd, "Hello, client!\n", 14, 0) == -1) {
                perror("send");
            }
            close(new_fd);
            exit(0);
        }

        close(new_fd);
        while (waitpid(-1, NULL, WNOHANG) > 0);
    }

    return 0;
}
