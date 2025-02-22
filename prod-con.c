/*pthread example.
Copyright (c) 2006-2007 Richard Palethorpe

Permission is hereby granted, free of charge, to any person obtaining a copy of this 
software and associated documentation files (the "Software"), to deal in the Software 
without restriction, including without limitation the rights to use, copy, modify, 
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
permit persons to whom the Software is furnished to do so, subject to the following 
conditions:

The above copyright notice and this permission notice shall be included in all copies 
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE

Website: richiejp.wordpress.com email: richiejp@gmail.com*/

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>

void* producer(void*);
void* consumer(void*);

/*This data structure contains information that needs to be shared between 
threads. It is passed to the producer and consumer threads' starter functions.
The alternative to this is to use global variables.*/
struct Context{
        //pthread_cond_t* cond;
        pthread_mutex_t* mutex;
        /*This is used to hold a character while it is passed from one thread to 
        another. Only the thread which owns the mutex lock should access it.*/
        long int* holder;
	int  index;
	int  limit;
        int  error;
};

int main(){
	int numOfProducer = 2;
        volatile struct Context context;
        //context.cond = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
        context.mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
        context.error = 0;
	context.limit = 100000000;
	context.holder = (long int*)malloc(context.limit*numOfProducer*sizeof(long int));
	context.index = 0;
         
        //pthread_cond_init(context.cond, NULL);
        pthread_mutex_init(context.mutex, NULL);
         
        pthread_t prod[numOfProducer]; 
        //pthread_t cons;
        
	const struct sched_param param = { 20 };

	int i;
        for(i=0; i<numOfProducer; i++){
                int ret;
                cpu_set_t cpuset;
                CPU_ZERO(&cpuset);
                CPU_SET(0, &cpuset);
		pthread_attr_t attr;
                pthread_attr_init(&attr);
                pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
                pthread_attr_setschedparam(&attr, &param);
                pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
                pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
                //printf("%d\n", sched_rr_get_interval())
		if((ret = pthread_create(&prod[i], &attr, producer, (void*)&context) != 0)){
		        printf("Could not create producer thread: %s\n", strerror(ret));

		        pthread_mutex_lock(context.mutex);
		        context.error = 1;
		        pthread_mutex_unlock(context.mutex);

		        pthread_mutex_destroy(context.mutex);
		        //pthread_cond_destroy(context.cond);
		        
		        return(EXIT_FAILURE);
		}
                struct sched_param schedparam;
                int policy;
                ret = pthread_getschedparam(prod[i], &policy, &schedparam);
                if(ret != 0) {
                        printf("error fetching schedparams\n");
                }
                //printf("thread created with policy = %d and priority = %d\n", policy, schedparam.sched_priority);
        }
        /*puts("createing second thread");
        if(pthread_create(&cons, NULL, consumer, (void*)&context) != 0){
                puts("Could not create consumer thread");
                        
                pthread_mutex_lock(context.mutex);
                context.error = 1;
                pthread_mutex_unlock(context.mutex);
                //pthread_cond_signal(context.cond);
                
                pthread_join(prod, NULL);
                
                pthread_mutex_destroy(context.mutex);
                //pthread_cond_destroy(context.cond);;
                
                return(EXIT_FAILURE);
        }*/
        
	for(i=0; i<numOfProducer; i++){
                //printf("%ld\n", prod[i]);
        	pthread_join(prod[i], NULL);
        }

	for(i=0; i<context.limit*numOfProducer; i+=100){
        	printf("%ld\n", context.holder[i]);
        }

	//pthread_join(cons, NULL);
        
        pthread_mutex_destroy(context.mutex);
        //pthread_cond_destroy(context.cond);
        
        //free(context.cond);
        free(context.mutex);
        free(context.holder);

        return(EXIT_SUCCESS);
}

void* producer(void* _context){
        //puts("in producer");
        struct Context* context = (struct Context*)_context;

	int i;
        for(i=0; i<context->limit; i++){
		pthread_mutex_lock(context->mutex);
	        if(!context->error){
                        context->holder[context->index] = pthread_self();
                        context->index ++;
			
                        //pthread_cond_signal(context->cond);
                        //pthread_cond_wait(context->cond, context->mutex);
                }else{
                        pthread_mutex_unlock(context->mutex);
                        
                        return NULL;
                }

		pthread_mutex_unlock(context->mutex);        
	}
        
        //pthread_cond_signal(context->cond);
        
        return NULL;
}

/*void* consumer(void* _context){
        puts("in consumer"); 
        struct Context* context = (struct Context*)_context;
        
        printf("Recieving data: "); 
        
        pthread_mutex_lock(context->mutex);
        while(context->holder != '\0'){
                if(!context->error){
                        putc((unsigned int)context->holder, stdout);
                        
                        //pthread_cond_signal(context->cond);
                        //pthread_cond_wait(context->cond, context->mutex);
                }else{
                        //pthread_cond_signal(context->cond);
                        //pthread_mutex_unlock(context->mutex);
                        
                        return NULL;
                }
        }
        
        pthread_cond_signal(context->cond);
        pthread_mutex_unlock(context->mutex);
        
        return NULL;
}*/
