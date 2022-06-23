#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>


void* loop(void* arg){
	puts("loop function running");
	int cnt = *((int*)arg);
	for(int i = 0; i < cnt; i++){
		printf("loop %d\n", i);
	}
	
}
void* thread_sub(void* arg){
	int i;
	int cnt = *((int*)arg);
	pthread_t t_id;
	puts("sub thread running");
	if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0){
		puts("pthread_create() error");
		return -1;
	}
	if(pthread_join(t_id, &thr_ret)!=0){
		puts("pthread_join() error");
		return -1;
	}
	printf("Finished loop : %s\n", (char*)thr_ret);
	char* msg = (char*)malloc(sizeof(char) * 50);
	char* txt = "hello, Finished sub thread";
	strcpy(msg, txt);
	return (void*)msg;


	//char* msg = (char*)malloc(sizeof(char) * 50);
	/*
	strcpy(msg, "hello, I'm thread~\n");

	for(i = 0; i < cnt; i++){
		sleep(1); puts("running thread");
	}
	return (void*)msg;
	*/
}

void* thread_main(void* arg){
	int i;
	int cnt = *((int*)arg);
	pthread_t t_id;
	void* thr_ret;

	char* msg = (char*)malloc(sizeof(char) * 50);
	char* txt = "hello, I'm thread_main";
	strcpy(msg, txt);
	
	puts("main thread running");

	if(pthread_create(&t_id, NULL, thread_sub, (void*)&thread_param) != 0){
		puts("pthread_create() error");
		return -1;
	}
	
	if(pthread_join(t_id, &thr_ret)!=0){
		puts("pthread_join() error");
		return -1;
	}
	printf("Finished thread sub : %s\n", (char*)thr_ret);
	return (void*)msg;

	//char* msg = (char*)malloc(sizeof(char) * 50);
	/*
	strcpy(msg, "hello, I'm thread~\n");

	for(i = 0; i < cnt; i++){
		sleep(1); puts("running thread");
	}
	return (void*)msg;
	*/
}

int main(int argc, char** argv){
	pthread_t t_id;
	int thread_param = 5;
	void* thr_ret;

	if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0){
		puts("pthread_create() error");
		return -1;
	}

	if(pthread_join(t_id, &thr_ret)!=0){
		puts("pthread_join() error");
		return -1;
	}

	puts("main running");

	printf("Thread return message : %s\n", (char*)thr_ret);
	free(thr_ret);
	return 0;
}
