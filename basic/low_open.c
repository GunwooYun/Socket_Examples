#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd;
	char buf[] = "Let's go!\n";

	fd = open("data.txt", O_CREAT|O_WRONLY|O_TRUNC);
	printf("file descriptor : %d\n", fd);

	close(fd);

	return 0;
}
