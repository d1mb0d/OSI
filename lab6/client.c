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
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);
    printf("Enter message: ");
    fgets(buf, BUF_SIZE, stdin);
    for (int i = 0; i < 10; ++i) {
        if (sendto(sock_fd, buf, strlen(buf), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
        sleep(2);
    }
    memset(buf, 0, BUF_SIZE);
    if (recvfrom(sock_fd, buf, BUF_SIZE, 0, NULL, NULL) == -1) {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }
    printf("Received message from server: %s\n", buf);
    close(sock_fd);
    return 0;
}