#include <stdio.h>
#include <unistd.h>

int gval = 10;
int main(int argc, char* argv[]){
	pid_t pid;
	int lval = 20;
	gval++, lval+= 5;

	pid = fork(); // return 0 : child

	if(!pid)
		gval += 2, lval += 2;
	else
		gval -= 2, lval -= 2;

	if(pid == 0)
		printf("child Proc : [%d %d] \n", gval, lval);
	else
		printf("parent Proc : [%d %d] \n", gval, lval);

	return 0;
}
