#include <stdio.h>
#include <pthread.h>
//#include <stdlib.h>
#include <unistd.h>

#define THREAD_NUM 10
void* thread_main(void * arg);

int main(){
	
	pthread_t tid_arr[THREAD_NUM];

	for(int i = 0; i < THREAD_NUM; i++){
		if(pthread_create(&tid_arr[i], NULL, thread_main, (void*)&i) != 0){
			puts("pthread create() error");
			return -1;
		}
	}

	sleep(20); puts("end of main");
	return 0;
}

void* thread_main(void * arg){
	int cnt = *((int *) arg);
	for(int i = 0; i < cnt; i++){
		printf("I'm [%d] thread\n", cnt);
		sleep(cnt);
	}
	return NULL;
}



