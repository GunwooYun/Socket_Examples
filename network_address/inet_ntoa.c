#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
	struct sockaddr_in addr1, addr2;
	char *str_ptr;
	char str_arr[20];

	addr1.sin_addr.s_addr = htonl(0x1020304);
	addr2.sin_addr.s_addr = htonl(0x1010101);

	str_ptr = inet_ntoa(addr1.sin_addr); // return the address which is allocated in memory
	strcpy(str_arr, str_ptr); // copy string
	printf("Dotted address1 : %s\n", str_ptr);

	inet_ntoa(addr2.sin_addr); // write data in the address already allocated
	printf("Dotted address2 : %s\n", str_ptr); // Value is changed because of previous line
	printf("Dotted address3 : %s\n", str_arr); // show copied string
	return 0;
}

