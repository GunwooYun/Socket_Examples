#include <stdio.h>
#include <pthread.h>

#define _REENTRANT

int sum = 0;

void* thread_summation(void* arg){
	unsigned int start = ((unsigned int*)arg)[0];
	unsigned int end = ((unsigned int*)arg)[1];
	
	while(start<=end){
		sum+= start;
		start++;
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t id_t1, id_t2;
	unsigned int range1[] = {1, 100000};
	unsigned int range2[] = {100001, 200000};

	unsigned int sum = 0;
	for(unsigned int i = 

	/* parameter : array */
	pthread_create(&id_t1, NULL, thread_summation, (void*)range1);
	pthread_create(&id_t2, NULL, thread_summation, (void*)range2);


	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);
	
	printf("result : %d\n", sum);

	return 0;
}

