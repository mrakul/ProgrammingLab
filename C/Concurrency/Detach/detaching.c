#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

// Define constants
#define NUM_OF_THREADS 10

void *funcToDo(void *arg)
{
    sleep(1);
    printf("A thread %llu finished the work\n", pthread_self());

    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t myThreads[NUM_OF_THREADS];
    pthread_attr_t detachedThreadAttr;
    pthread_attr_init(&detachedThreadAttr);
    pthread_attr_setdetachstate(&detachedThreadAttr, PTHREAD_CREATE_DETACHED);

    // 1. Create threads sequentially
    for (int i = 0; i < NUM_OF_THREADS; i++){
        pthread_create(&myThreads[i], &detachedThreadAttr, funcToDo, NULL);                        //
        //pthread_detach(myThreads[i]);                                             // After detaching, thread is responsible to release the resources itself AND we can't join to it anymore
    }                                                                               // Note: no need to make detach if creating threads initially using attributes of detached thread
    // 2. Wait for the threads to finish                                            // Should no wait for the threads, since we are creating it as detached
    // for (int i = 0; i < NUM_OF_THREADS; i++)
    //     if (pthread_join(myThreads[i], NULL) != 0)
    //         printf("Failed to join a thread %d\n", i);

    // Here, if exit from the main thread by pthread_exit() instead of return, the process will be waiting for the rest of the remaining threads
    pthread_exit(0);
    //return 0;
}