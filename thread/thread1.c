#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void* thread_main(void* arg);

	int data = 0;
int main(int argc, char** argv){
	pthread_t t_id1;
	pthread_t t_id2;
	int thread_param = 5;

	int id1 = 1, id2 = 2;
	


	if(pthread_create(&t_id1, NULL, thread_main, (void*)&id1)!=0){
		puts("pthread_create() error");
		return -1;
	};
	if(pthread_create(&t_id2, NULL, thread_main, (void*)&id2)!=0){
		puts("pthread_create() error");
		return -1;
	};
	for(int i = 0; i < thread_param*2; i++){
		puts("main running");
		sleep(1);
	}
	puts("end of main");

	return 0;
}


void* thread_main(void* arg){
	int cnt = 10;
	int id = *((int *)arg);
	for(int i = 0; i < cnt; i++){
		printf("thread[%d] : %d\n", id, ++data);
		sleep(1);
		//puts("running thread");
	}
	return NULL;
}
