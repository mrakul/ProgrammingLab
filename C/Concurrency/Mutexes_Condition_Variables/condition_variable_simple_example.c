#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

pthread_cond_t conditionVariable = PTHREAD_COND_INITIALIZER;
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

int sharedVariable = 100;
bool isNotified = false;

void *reporterThreadFunc(void *unused)
{
    // Lock the mutex, wait by the condition variable and only after getting the signal report and unlock the mutex
    pthread_mutex_lock(&myMutex);
    // while (!isNotified){                                       // isNotified polling to check is one approach, but it consumes CPU not effectively (while is used when it is complicated condition, some threads may be woken up, and then check it again)
    pthread_cond_wait(&conditionVariable, &myMutex);              // Note that the myMutex address should be passed also, that is the mutex associated with the condition variable
    // Note: When pthread_cond_wait() is called, the calling thread must have mutex locked.
    // The pthread_cond_wait() function atomically unlocks mutex and performs the wait for the condition.
    // }

    printf("The sharedVariable is %d\n", sharedVariable);
    pthread_mutex_unlock(&myMutex);

    return NULL;
}

void *assignerThreadFunc(void *unused)
{
    sharedVariable = 20;                                            // Change the shared variable value. Note that this is not covered by the mutex, this is done on the reporter side

    // Lock the mutex, change the isNotified variable value and signal by the conditionVariable
    pthread_mutex_lock(&myMutex);
    // isNotified = true;
    pthread_cond_signal(&conditionVariable);
    pthread_mutex_unlock(&myMutex);

    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t reporterThread, assignerThread;

    // Intentionally launch the reporter thread first, and after the assigner thread
    pthread_create(&reporterThread, NULL, reporterThreadFunc, NULL);
    pthread_create(&assignerThread, NULL, assignerThreadFunc, NULL);

    // Wait for the threads
    void *unusedRetCode;
    pthread_join(reporterThread, &unusedRetCode);
    pthread_join(assignerThread, &unusedRetCode);

    return 0;
}