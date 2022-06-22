#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[]){
	int serv_sock, clnt_sock; // file descriptor
	char msg[BUF_SIZE]; // message buffer
	int str_len; // message length

	struct sockaddr_in serv_adr, clnt_adr; // socket struct
	socklen_t clnt_adr_sz; // struct clnt_adr size

	if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

	/* Create Socket */
	serv_sock = socket(PF_INET, SOCK_STREAM, 0); // IPv4, TCP
	if(serv_sock == -1)
		error_handling("socket() error");
	memset(&serv_adr, 0, sizeof(serv_adr)); // set struct as 0
	serv_adr.sin_family = AF_INET; // IPv4
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); // little->big endian, dynamic address
	serv_adr.sin_port = htons(atoi(argv[1])); // little -> big endian port

	/* bind() */
	if(bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	
	/* listen() */
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	clnt_adr_sz = sizeof(clnt_adr);

	for(int i = 0; i < 5; i++){
		/* accept() */
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		if(clnt_sock == -1)
			error_handling("accept() error");
		else
			printf("Client connected %d \n", i+1);

		while((str_len = read(clnt_sock, msg, BUF_SIZE)) != 0) // return read length
		{
			//printf("string length from client : %d\n", str_len);
			//*(msg+str_len) = '\0';
			msg[str_len] = 0;
			printf("Messeage from client : %s", msg);
			write(clnt_sock, msg, str_len);
		}
		close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}
