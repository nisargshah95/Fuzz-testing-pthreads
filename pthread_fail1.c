#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* this function is run by the second thread */
void *inc_x(void *x_void_ptr)
{
	// sleep(1);
	struct sched_param schedparam;
	int policy;
	int ret = pthread_getschedparam(pthread_self(), &policy, &schedparam);
	if(ret != 0) {
		printf("error fetching schedparams\n");
	}
	printf("thread created with policy = %d and priority = %d\n", policy, schedparam.sched_priority);

	/* increment x to 100 */
	int **x = (int **)x_void_ptr;
	(**x)++;
	printf("x increment finished = %d\n", **x);

	/* the function must return something - NULL will do */
	return NULL;
}

int main()
{
	int *x = NULL;
	//printf("x = %d\n", *x);
	pthread_t inc_x_thread;

	/* create a second thread which executes inc_x(&x) */
	int ret;
	if((ret = pthread_create(&inc_x_thread, NULL, inc_x, &x)) != 0) {
		fprintf(stderr, "Error creating thread = %d\n", ret);
		return ret;
	}
	// sleep(1);
	if (!(x = (int *)malloc(sizeof(int)))) {
		fprintf(stderr, "Error allocating memory for x\n");
		return 1;
	}

	/* wait for the second thread to finish */
	if((ret = pthread_join(inc_x_thread, NULL)) != 0) {
		fprintf(stderr, "Error joining thread = %d\n", ret);
		return ret;
	}

	printf("x: %d\n", *x);

	return 0;
}
