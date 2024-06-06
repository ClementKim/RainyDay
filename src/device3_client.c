#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../header/speaker.h"

#define BUFFER_MAX 3
#define DIRECTION_MAX 256
#define VALUE_MAX 256

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char msg[2];
    char on[2] = "1";
    int str_len;

    if (argc != 3) {
    printf("Usage : %s <IP> <port>\n", argv[0]);
    exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    printf("Connection established\n");

    while (1) {
        str_len = read(sock, msg, sizeof(msg));

        if (str_len == -1)
            error_handling("read() error");

        if (!strcmp(msg, msg, 1))
            buzzer();
    }

    close(sock);

    return 0;
}
