#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_SIZE 100

void error_handling(char *msg);

int main(int argc, char *argv[]){

	char buf[BUF_SIZE];
	
	int serv_sock; // fd for server socket
	int clnt_sock; // fd for client socket
	int fd; // fd for file

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

	socklen_t clnt_addr_size;

	int str_len = 0;

	if(argc != 3){
		printf("Usage : %s <port> <file>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0); // Create socket
	if(serv_sock < 0){
		error_handling("socket() error");
	}


	memset(&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		error_handling("bind() error");
	}

	if(listen(serv_sock, 5) < 0){
		error_handling("listen() error");
	}

	clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
	if(clnt_sock < 0){
		error_handling("accept() error");
	}

	fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd < 0){
		error_handling("open() error");
	}


	while(1) // return read length
	{
		str_len = read(clnt_sock, buf, sizeof(buf));
		printf("read : %d\n", str_len);
		if(str_len == 0)
			break;
		
		if(write(fd, buf, str_len) < 0){
			error_handling("write() error");
		}
		
	}

	printf("Done..\n");
	close(fd);
	printf("close fd\n");
	close(clnt_sock);
	printf("close client socket\n");
	close(serv_sock);
	printf("close server socket\n");

	return 0;
}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
