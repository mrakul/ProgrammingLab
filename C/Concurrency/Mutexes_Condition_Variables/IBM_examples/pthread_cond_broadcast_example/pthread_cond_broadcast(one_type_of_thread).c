#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define _MULTI_THREADED

/* For safe condition variable usage, must use a boolean predicate and a mutex with the condition. */
int conditionToUnlockThreads = 0;
pthread_cond_t conditionVariable = PTHREAD_COND_INITIALIZER;
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

#define NUM_OF_THREADS 10

void *threadFunc(void *parm)
{
    printf("Thread created\n");
    pthread_mutex_lock(&myMutex);
    while (!conditionToUnlockThreads){                               // We are blocking the threads until some condition happens
        printf("Thread blocked\n");
        pthread_cond_wait(&conditionVariable, &myMutex);
    }
    printf("A thread is unlocked here\n");                              // Thread is unlocked since while check passed the condition
    pthread_mutex_unlock(&myMutex);
    return NULL;
}

int main(int argc, char **argv)
{
    int i;
    pthread_t threadsIDs[NUM_OF_THREADS];

    // Before creating any threads
    printf("Before creating any threads, the program is: %s\n", argv[0]);

    // 1. Create 10 threads which are waiting for the signal
    printf("Create %d threads\n", NUM_OF_THREADS);
    for (i = 0; i < NUM_OF_THREADS; ++i){
        pthread_create(&threadsIDs[i], NULL, threadFunc, NULL);
    }

    printf("===> %d threads created \n Main thread sleeps for 3 seconds...\n", NUM_OF_THREADS);
    sleep(3);                                                               /* Sleep is not a very robust way to serialize threads */

    // 2. Main thread locks the mutex, changes the condition AND notifies ALL the threads by pthread_cond_broadcast() which are waiting on that condition variable
    pthread_mutex_lock(&myMutex);

    conditionToUnlockThreads++;                                             // Increment the condition
    printf("Wake up all waiting threads...\n");
    pthread_cond_broadcast(&conditionVariable);                             // This wakes up ALL THE THREADS waiting on the conditional variable

    pthread_mutex_unlock(&myMutex);

    // 3. Wait for all the threads
    printf("Wait for threads and cleanup\n");
    for (i = 0; i < NUM_OF_THREADS; ++i){
        pthread_join(threadsIDs[i], NULL);
    }

    // 4. Uninitialize the mutex and the condition variable (optional?)
    pthread_cond_destroy(&conditionVariable);
    pthread_mutex_destroy(&myMutex);

    return 0;
}