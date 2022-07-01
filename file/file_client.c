#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 100

void error_handling(char *msg);

int main(int argc, char* argv[]){
	int sock; // fd for socket
	int fd; // fd for file
	struct sockaddr_in serv_addr; // socket struct
	int str_len;
	char buf[BUF_SIZE];
	int recv_cnt, recv_len;

	if(argc != 4){
        printf("Usage : %s <IP> <port> <send_file>\n", argv[0]);
        exit(1);
    }

	/* Create Socket */
    sock = socket(PF_INET, SOCK_STREAM, 0); // IPv4, TCP
    if(sock < 0)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr)); // Init 0
    serv_addr.sin_family = AF_INET; // IPv4
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // ip address
    serv_addr.sin_port = htons(atoi(argv[2])); // port

	/* Connect Socket */
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		error_handling("connect() error");
	else
		puts("Connected");

	fd = open(argv[3], O_RDONLY); // read only
	if(fd < 0){
		error_handling("open() error");
	}

	while((str_len = read(fd, buf, BUF_SIZE)) != 0) // return read length
    {
        if(write(sock, buf, str_len) == -1){
            error_handling("write() error");
        }

    }
	printf("Done..\n");
    close(fd);
    printf("close fd\n");
    close(sock);
    printf("close socket\n");
	return 0;
}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
