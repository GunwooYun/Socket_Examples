#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	
	int sock;
	char send_msg[100] = {0};
	
	struct sockaddr_in serv_addr; // To connect socket

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1){
		printf("socket() error\n");
		exit(1);
	}

	//int memset_rst = memset(&serv_addr, 0, sizeof(serv_addr);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
		printf("connect() error\n");
		exit(1);
	}
	else
		printf("connected\n");

	while(1){
		fputs("write message : ", stdout);
		fgets(send_msg, 100, stdin);

		if(!strcmp(send_msg, "q\n"))
			break;

		write(sock, send_msg, strlen(send_msg));
	}
	close(sock);
	return 0;
}







	

