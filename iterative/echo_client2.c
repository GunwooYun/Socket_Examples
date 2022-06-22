#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]){
	int sock; // file descriptor
	struct sockaddr_in serv_addr; // socket struct
	int str_len;
	char msg[BUF_SIZE];
	int recv_cnt, recv_len;

	if(argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

	/* Create Socket */
    sock = socket(PF_INET, SOCK_STREAM, 0); // IPv4, TCP
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr)); // Init 0
    serv_addr.sin_family = AF_INET; // IPv4
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // ip address
    serv_addr.sin_port = htons(atoi(argv[2])); // port

	/* Connect Socket */
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error");
	else
		puts("Connected");

	while(1){
		fputs("Input message(Q to quit) : ", stdout);
		fgets(msg, BUF_SIZE, stdin);

		if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
			break;
		str_len = write(sock, msg, strlen(msg)); // get write length
		//str_len = read(sock, msg, BUF_SIZE-1);
		recv_len = 0;
		while(recv_len < str_len){

			recv_cnt = read(sock, &msg[recv_len], BUF_SIZE-1);
			if(recv_cnt == -1)
				error_handling("read() error!");
			recv_len += recv_cnt;
		}
		msg[str_len] = 0;
		printf("Message from server : %s\n", msg);
	}
	close(sock);
	return 0;
}
