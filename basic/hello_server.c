#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TRUE 1
#define FALSE 1


void error_handling(char *msg){
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char *argv[]){
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char msg[] = "Hello World!";

	if(argc != 2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	/* Create Socket */
	serv_sock = socket(PF_INET, SOCK_STREAM, 0); // socket(int domain, int type, int protocol)
	if(serv_sock == -1)
		error_handling("socket() error");

	/* Initialize struct serv_addr as 0 */
	memset(&serv_addr, 0, sizeof(serv_addr));
	if(&serv_addr == NULL)
		error_handling("serv_addr : memset() error");

	serv_addr.sin_family = AF_INET; // AF_INET : IPv4 Internet Protocol
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //
	serv_addr.sin_port = htons(atoi(argv[1])); //

	/* Bind error */
	int option = TRUE;
	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, sizeof(option));

	/* Bind Socket : IP address, PORT */
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	/* Listen Socket : make state connectable */
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	/* Set Client Socket */
	clnt_addr_size = sizeof(clnt_addr);

	printf("before accept()\n");

	/* Accept Socket : Wait for connection */
	clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
	if(clnt_sock == -1)
		error_handling("accept() error");

	write(clnt_sock, msg, sizeof(msg));
	close(clnt_sock);
	close(serv_sock);

	return 0;
}
