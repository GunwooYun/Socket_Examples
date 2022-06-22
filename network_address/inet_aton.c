/***************************************************************
* inet_aton : string type of address with dot -> 32bit integer *
* --> save the value to sockaddr_in.sin_addr                   *
* --> Need two parameters, (string, member of struct)          *
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void error_handling(char *msg){
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(){
	char * addr = "127.232.124.79";
	struct sockaddr_in addr_inet;

	if(!inet_aton(addr, &addr_inet.sin_addr))
		error_handling("Conversion error");
	else
		printf("Network ordered integer addr : %#x \n", addr_inet.sin_addr.s_addr);

	return 0;
}
