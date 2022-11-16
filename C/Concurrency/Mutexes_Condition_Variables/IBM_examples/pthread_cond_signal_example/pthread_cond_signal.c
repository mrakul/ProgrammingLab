#define _MULTI_THREADED
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>

int workToDo = 0;                                                           // No work initially
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

#define NUM_OF_THREADS 2
#define NUM_OF_JOBS 10

void *threadFunc(void *parm)
{
    // Usually worker threads will loop on these operations
    while (1){
        pthread_mutex_lock(&myMutex);

        while (!workToDo){
            printf("A Thread blocked\n");
            pthread_cond_wait(&cond, &myMutex);
        }
        printf("A Thread %llu unblocked\n", pthread_self());

        // As if the current task took the work
        workToDo = 0;                                                       // Here we imitating that there is no work to take
        pthread_mutex_unlock(&myMutex);
        sleep(1);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t threadsIDs[NUM_OF_THREADS];

    // Before creating any threads
    printf("Before creating any threads, the program is: %s\n", argv[0]);

    // 1. Create NUM threads waiting for the condition variable
    printf("Create %d threads\n", NUM_OF_THREADS);
    for (int i = 0; i < NUM_OF_THREADS; ++i)
        pthread_create(&threadsIDs[i], NULL, threadFunc, NULL);

    printf("Main thread %llu sleeps for 3 seconds...\n", pthread_self());
    sleep(3);

    // 2. Repeat the cycle NUM_OF_JOBS times: here the dispatchering main thread is imitated. When the work exists, ONE thread is signaled
    for (int i = 0; i < NUM_OF_JOBS; ++i){
        printf("Wake up a worker, work to do...\n");
        pthread_mutex_lock(&myMutex);
        // In the real world, all the threads might be busy, and we would add work to a queue instead of simply using a flag
        //  In that case the boolean predicate might be some boolean statement like: if (the-queue-contains-work)
        if (workToDo)
            printf("Work already presents, likely threads are busy\n");

        workToDo = 1;

        pthread_cond_signal(&cond);                                             // If no threads are waiting, this has no effect, that is the statement above notifies that work already presents
        pthread_mutex_unlock(&myMutex);
        // sleep(1);
    }

    return 0;
}