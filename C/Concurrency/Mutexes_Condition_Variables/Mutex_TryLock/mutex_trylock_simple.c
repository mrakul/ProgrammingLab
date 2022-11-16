#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

// Define constants
#define NUM_OF_THREADS 10

// Define synchronization variables
pthread_mutex_t mutexToLock;

void *funcToDo(void *arg)
{
    int tryLockResult;
    if ((tryLockResult = pthread_mutex_trylock(&mutexToLock)) == 0){
        printf("==> A Thread got the lock\n");
        pthread_mutex_unlock(&mutexToLock);
    }
    else if (tryLockResult == EBUSY)
        printf("XXX A thread didn't got the lock\n");

    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t myThreads[NUM_OF_THREADS];

    // 0. Initialization
    pthread_mutex_init(&mutexToLock, NULL);

    // 1. Create threads sequentially
    for (int i = 0; i < NUM_OF_THREADS; i++)
        pthread_create(&myThreads[i], NULL, funcToDo, NULL);

    // 2. Wait for the Producers threads to finish
    for (int i = 0; i < NUM_OF_THREADS; i++)
        pthread_join(myThreads[i], NULL);
    printf("==> Right after all the Producers finished their work\n");

    pthread_mutex_destroy(&mutexToLock);

    return 0;
}