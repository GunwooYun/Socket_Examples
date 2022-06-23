#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD 100

long long num = 0; // 64bit data type
pthread_mutex_t mutex;

void* thread_inc(void* arg){
	int i;
	pthread_mutex_lock(&mutex);
	for(i = 0; i<50000000; i++)
		num+= 1;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void* thread_des(void* arg){
	int i;
	for(i = 0; i<50000000; i++){
	pthread_mutex_lock(&mutex);
		num-= 1;
	pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t threads_id[NUM_THREAD]; // Delcare array of thread
	int i;

	/* int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr); */
	pthread_mutex_init(&mutex, NULL);

	printf("sizeof long long : %ld\n", sizeof(long long));
	for(i = 0; i<NUM_THREAD; i++){
		if(i%2)
			pthread_create(&(threads_id[i]), NULL, thread_inc, NULL);
		else
			pthread_create(&(threads_id[i]), NULL, thread_des, NULL);
	}
	
	for(i=0; i<NUM_THREAD; i++){
		pthread_join(threads_id[i], NULL);
	}

	printf("result : %lld \n", num);
	/* int pthread_mutex_destroy(pthread_mutex_t *mutex) */
	pthread_mutex_destroy(&mutex);
	return 0;
}

