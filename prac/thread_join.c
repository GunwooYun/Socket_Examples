#include <stdio.h>
#include <pthread.h>
#include <string.h>
//#include <pthread.h>

void* thread_main(void * arg);

int main(int argc, char* argv[]){
	pthread_t t_id; // thread id
	int thread_param = 5;
	void * thr_ret;

	/*
	  int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr,
	  void*(*start_routine)(void*), void * restrict arg );
	 */
	if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0){
		puts("pthread_create() error");
		return -1;
	};
	sleep(10); puts("end of main");
	return 0;
}

/* thread function */
void* thread_main(void * arg){
	int i;
	int cnt = *((int *)arg);
	for(i = 0; i < cnt; i++){
		sleep(1); puts("running thread");
	}
	return NULL;
}
