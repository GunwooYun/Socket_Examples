#include <stdio.h>

int add(int a, int b){
	return a+b;
}


int main(){
	int(*fp)(int, int);
	fp = add;

	printf("%d\n", fp(1,1));

	return 0;
}
