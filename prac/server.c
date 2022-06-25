#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h> // htonl(), INADDR_ANY
#include <string.h>

int main(int argc, char* argv[]){
	int serv_sock, clnt_sock; // socket file descriptor
	unsigned short port;

	/* Create socket, open file, return file descriptor number */
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock < 0){
		printf("create socket failed\n");
		exit(1);
	}
	//clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
	/*
	if(clnt_sock < 0){
		printf("create socket failed\n");
		exit(1);
	}
	*/
	//printf("%d\n", PF_INET);

	struct sockaddr_in serv_addr; // address information struct

	memset(&serv_addr, 0, sizeof(serv_addr)); // init 0
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	printf("%s\n", argv[1]);
	printf("%d\n", atoi(argv[1]));
	port = atoi(argv[1]);
	printf("%d\n", port);
	port = htons(port);
	printf("%d\n", port);

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
		printf("bind() error\n");
		exit(1);
	}

	if(listen(serv_sock, 3) < 0){
		printf("listen() error\n");
		exit(1);
	}

	socklen_t clnt_sock_size = sizeof(clnt_sock);
	clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_sock, &clnt_sock_size);
	if(clnt_sock < 0){
		printf("accept() error\n");
		exit(1);
	}
	char msg[100] = "hello, world";
	write(clnt_sock, msg, sizeof(msg));
	//printf("server socket file descriptor number : %d\n", serv_sock);
	//printf("client socket file descriptor number : %d\n", clnt_sock);

	close(serv_sock); // close socket file
	close(clnt_sock); // close socket file
	return 0;

}
