#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

// Define constants
#define NUM_OF_THREADS 10                                               // Note: if NUM_OF_THREADS is divisible on BARRIER_LEVEL, in the configuration below the barrier will allow to pass by portions immediately (21 and 7, for example)
#define BARRIER_LEVEL 7

// Define synchronization variables
pthread_mutex_t mutexToLock;
pthread_barrier_t myBarrier;

void *funcToDo(void *arg)
{
    while (1){
        printf("A thread waiting before the barrier ...\n");
        sleep(1);                                                       // Delay to have a chance to see that all the threads are waiting

        pthread_barrier_wait(&myBarrier);                               // Here, the waiting BARRIER_LEVEL num of threads are passed the barrier, but leaves the rest until BARRIER_LEVEL will be reached
        printf("A thread passed the barrier here. \n");
        sleep(1);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t myThreads[NUM_OF_THREADS];

    // 0. Initialization
    pthread_mutex_init(&mutexToLock, NULL);
    pthread_barrier_init(&myBarrier, NULL, BARRIER_LEVEL);

    // 1. Create threads sequentially
    for (int i = 0; i < NUM_OF_THREADS; i++)
        pthread_create(&myThreads[i], NULL, funcToDo, NULL);

    // 2. Wait for the Producers threads to finish
    for (int i = 0; i < NUM_OF_THREADS; i++)
        pthread_join(myThreads[i], NULL);
    printf("==> Right after all the Producers finished their work\n");

    // 3. Destroyingt
    pthread_mutex_destroy(&mutexToLock);
    pthread_barrier_destroy(&myBarrier);

    return 0;
}