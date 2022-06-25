#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

	int fd;
	char buf[100];

	fd = open("./test", O_RDONLY);

	if(fd == -1){
		printf("file open error\n");
		exit(1);
	}

	int read_len = read(fd, buf, sizeof(buf));
	
	printf("read() return value : %d\n", read_len);

	close(fd);

	return 0;
}


	
