#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

void error_handling(char *msg);
void * send_msg(void* arg);
void * recv_msg(void* arg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

int main(int argc, char** argv){
	int sock; // file descriptor
	struct sockaddr_in serv_adr; // socket struct
	pthread_t send_thread, recv_thread; // thread
	void* thread_return;

	if(argc != 4){
		printf("Usage : %s <IP> <port> <name>\n", argv[0]);
		exit(1);
	}

	sprintf(name, "[%s]", argv[3]); // [name]
	
	/* Create Socket */
	sock = socket(PF_INET, SOCK_STREAM, 0);


	/* struct sockaddr_in set as 0 , 16 byte, sin_family, sin_port, sin_addr.s_addr, sin_zero*/
	memset(&serv_adr, 0, sizeof(serv_adr));

	/* Initialize struct sockaddr_in IPv4, TCP */
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]); // 
	serv_adr.sin_port = htons(atoi(argv[2])); // convert port string to intger, and little -> big

	/* Connect() */
	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error");

	pthread_create(&send_thread, NULL, send_msg, (void*)&sock);
	pthread_create(&recv_thread, NULL, recv_msg, (void*)&sock);
	pthread_join(send_thread, &thread_return); // get return value
	pthread_join(recv_thread, &thread_return); // get return value
	close(sock);
	return 0;
}

void* send_msg(void* arg){
	int sock = *((int *)arg); // sock file descriptor
	char name_msg[NAME_SIZE+BUF_SIZE];
	while(1){
		fgets(msg, BUF_SIZE, stdin); // Get string from stdin as BUF_SIZE
		if(!strcmp(msg,"q\n") || !strcmp(msg,"Q\n")){
			close(sock);
			exit(0);
		}
		sprintf(name_msg, "%s %s", name, msg);
		write(sock, name_msg, strlen(name_msg));
	}
	return NULL;
}


void* recv_msg(void* arg){
	int sock = *((int *)arg); // sock file descriptor
	char name_msg[NAME_SIZE+BUF_SIZE];
	int str_len;
	while(1){
		str_len = read(sock, name_msg, NAME_SIZE+BUF_SIZE-1);
		if(str_len == -1) return (void*)-1;
		name_msg[str_len] = 0;
		fputs(name_msg, stdout);
		}
	return NULL;
}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

