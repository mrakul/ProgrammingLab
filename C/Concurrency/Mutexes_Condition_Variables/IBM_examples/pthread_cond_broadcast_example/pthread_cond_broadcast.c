#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define _MULTI_THREADED
/***
// My understanding is that pthread_cond_broadcast is used when different types of threads are used.
// By checking the condition to unlock the threads, we can unlock some threads staying another locked.
***/


// In this example, conditionToUnlock threads have several levels and two types of threads
int conditionToUnlockThreads = 0;
pthread_cond_t conditionVariable = PTHREAD_COND_INITIALIZER;
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

#define NUM_OF_THREADS 10
#define MAX_CONDITION 5

// These threads are free when conditionToUnlockThreads is more than 1 (=2)
void *threadFunc1(void *parm)
{
    printf("Thread TYPE1 created\n");
    pthread_mutex_lock(&myMutex);
    while (conditionToUnlockThreads < MAX_CONDITION - 3){                     // We are blocking the threads until some condition happens
        printf("Thread TYPE1 blocked\n");
        pthread_cond_wait(&conditionVariable, &myMutex);
    }
    printf("A thread TYPE1 is unlocked here\n");                              // Thread is unlocked since while check passed the condition
    pthread_mutex_unlock(&myMutex);
    return NULL;
}

// These threads are free when the conditionToUnlockThreads is more than 3 (=4)
void *threadFunc2(void *parm)
{
    printf("Thread TYPE2 created\n");
    pthread_mutex_lock(&myMutex);
    while (conditionToUnlockThreads < MAX_CONDITION - 1){                     // We are blocking the threads until some condition happens
        printf("Thread TYPE2 blocked\n");
        pthread_cond_wait(&conditionVariable, &myMutex);
    }
    printf("A thread TYPE2 is unlocked here\n");                              // Thread is unlocked since while check passed the condition
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
    for (i = 0; i < NUM_OF_THREADS; i++){
        if (i & 1)                                                               // Split to odd and even threads
            pthread_create(&threadsIDs[i], NULL, threadFunc1, &i);
        else
            pthread_create(&threadsIDs[i], NULL, threadFunc2, &i);
    }

    printf("===> %d threads created \n Main thread sleeps for 3 seconds...\n", NUM_OF_THREADS);
    sleep(3);                                                                    // Sleep is not a very robust way to serialize threads

    // 2. Main thread locks the mutex, changes the condition AND notifies ALL the threads by pthread_cond_broadcast() which are waiting on that condition variable
    // Change the condition up to MAX value, incrementing by 1 at one iteration
    for (int i = 0; i < MAX_CONDITION; i++){
        printf("===> Iteration %d\n", i);                                       // Print out the number of iteration

        pthread_mutex_lock(&myMutex);
        //conditionToUnlockThreads++;                                           // Increment the condition
        conditionToUnlockThreads = i;                                           // Better to link it with incrementing variable for clearness
        printf("Wake up all waiting threads...\n");                             // After incrementing, ALL THE THREADS are woken up
        pthread_cond_broadcast(&conditionVariable);                             // This wakes up ALL THE THREADS waiting on the conditional variable
        printf("===> Condition changed to: %d. Main thread sleeps for 3 seconds...\n", i);

        pthread_mutex_unlock(&myMutex);
        sleep(3);                                                               // This is to wait until all the threads will be in waiting state
    }

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