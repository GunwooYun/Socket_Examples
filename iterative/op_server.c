#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int calculate(int opnum, int opnds[], char op){

	int result = opnds[0], i;
	switch(op){
		case '+':
			for(i=1;i < opnum; i++) result += opnds[i];
			break;
		case '-':
			for(i=1;i < opnum; i++) result -= opnds[i];
			break;
		case '*':
			for(i=1;i < opnum; i++) result *= opnds[i];
			break;
	}
	return result;
}


int main(int argc, char *argv[]){
	int serv_sock, clnt_sock; // file descriptor
	char opinfo[BUF_SIZE]; // message buffer
	int result, opnd_cnt, i;
	int recv_cnt, recv_len;
	struct sockaddr_in serv_adr, clnt_adr; // socket struct
	socklen_t clnt_adr_sz; // struct clnt_adr size
	int str_len; // message length


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
		opnd_cnt = 0;
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		if(clnt_sock == -1)
			error_handling("accept() error");
		else
			printf("Client connected %d \n", i+1);

		read(clnt_sock, &opnd_cnt, 1); // read 1 byte of operand count

		recv_len = 0;
		while((opnd_cnt * OPSZ+1) > recv_len) // OPSZ = 4byte -> (operand_count * 4byte) + 1byte(operator)
		{
			/* read(file descriptor, buffer to be saved, read size */
			recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE-1);
			recv_len += recv_cnt; // recevied length = recevied length + recevied count
		}
		result = calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]); // Need to read 4byte of array, so (int*), operator is saved opinfo[last index]
		printf("result : %d\n", result);
		write(clnt_sock, (char*)&result, sizeof(result)); // send result value to client
		close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}
