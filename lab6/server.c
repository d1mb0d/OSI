#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 512
#define PORT 7777

int main(void) {
    int sock_fd;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buf[BUF_SIZE];
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    if (bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    while (1) {
        memset(buf, 0, BUF_SIZE);
        if (recvfrom(sock_fd, buf, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &client_len) == -1) {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }
        printf("Received message from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        printf("Message: %s\n", buf);
        if (sendto(sock_fd, buf, strlen(buf), 0, (struct sockaddr *)&client_addr, client_len) == -1) {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
        printf("Sent message to %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }
    return 0;
}
