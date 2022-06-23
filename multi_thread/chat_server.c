#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

int clnt_cnt = 0; // client count
int clnt_socks[MAX_CLNT]; // client socket array
pthread_mutex_t mutx; // declare mutex

void error_handling(char *msg);
void send_msg(char* msg, int len);
void * handle_clnt(void* arg);

int main(int argc, char** argv){
	int serv_sock, clnt_sock; // file descriptor
	struct sockaddr_in serv_adr, clnt_adr; // socket struct
	int clnt_adr_sz; //
	pthread_t t_id; // thread id

	if(argc != 2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	/* int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr); */
	pthread_mutex_init(&mutx, NULL); // Initialize mutex

	serv_sock = socket(PF_INET, SOCK_STREAM, 0); // IPv4, TCP

	/* struct sockaddr_in set as 0 , 16 byte, sin_family, sin_port, sin_addr.s_addr, sin_zero*/
	memset(&serv_adr, 0, sizeof(serv_adr));

	/* Initialize struct sockaddr_in IPv4, TCP */
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); // 
	serv_adr.sin_port = htons(atoi(argv[1])); // convert port string to intger, and little -> big

	/* bind(), save value of sockaddr_in into socket */
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");

	/* listen() */
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	while(1){
		clnt_adr_sz = sizeof(clnt_adr); // 16byte
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); // Create Scoket for client

		/* Access global variable : clnt_cnt */
		pthread_mutex_lock(&mutx); // lock
		clnt_socks[clnt_cnt++] = clnt_sock; // Save socket into array of socket
		pthread_mutex_unlock(&mutx); // unlock

		/* Make thread, and give parameter socket */
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
		pthread_detach(t_id);
		printf("Connected client IP : %s\n", inet_ntoa(clnt_adr.sin_addr));
	}
	close(serv_sock);
	return 0;
}

void send_msg(char* msg, int len){
	int i;
	/* Thread access global variable : clnt_cnt */
	pthread_mutex_lock(&mutx); // lock
	for(i = 0; i < clnt_cnt; i++)
		write(clnt_socks[i], msg, len);
	pthread_mutex_unlock(&mutx); // unlock
}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

void * handle_clnt(void* arg){
	int clnt_sock = *((int *)arg); // void* -> int*
	int str_len = 0, i;
	char msg[BUF_SIZE];

	/* Read client message */
	while((str_len = read(clnt_sock, msg, sizeof(msg))) != 0){
		printf("%d\n", str_len);
		send_msg(msg, str_len);
	}

	/* Thread access global variable : clnt_cnt */
	pthread_mutex_lock(&mutx); // lock
	for(i = 0; i < clnt_cnt; i++){
		if(clnt_sock == clnt_socks[i]){
			while(i++ < clnt_cnt - 1)
				clnt_socks[i] = clnt_socks[i+1];
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx); // unlock
	close(clnt_sock);
	return NULL;
}


