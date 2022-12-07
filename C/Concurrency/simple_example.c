#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

const int NUM_OF_THREADS = 1000;

pthread_mutex_t mutexToSync = PTHREAD_MUTEX_INITIALIZER;                            // Create mutex to lock the critical section

void *funcToThread(void *num)                                                       // Function for thread is void *(*func)(void *)
{
    // Race conditions: operation below is not atomic, so may observed in output: 11, 12, 15, 14, 16, 13 ...
    pthread_mutex_lock(&mutexToSync);
    (*((int *)num))++;                                                              // Increment num by casting to (int *) and dereferencing it to get lvalue (but postfix increment returns rvalue)
    pthread_mutex_unlock(&mutexToSync);
    printf("Inside thread: num = %d\n", *((int *)num));

    // pthread_exit(NULL);
    return num;                                                                     // Here we return an address of the passed address as input parameter, just as example
}

int main(int argc, const char **argv)
{
    pthread_t myThreads[NUM_OF_THREADS];                                            // Create several threads variables
    int localNum = 10;                                                              // Initialize local variable which will be modified by the threads

    for (int i = 0; i < NUM_OF_THREADS; i++)
        pthread_create(&myThreads[i], NULL, funcToThread, (void *)&localNum);       // Create threads in parallel and pass the parameter localNum's address

    void *retFromThread;                                                            // Return from thread (pointer to void)
    int intRCThread;                                                             // int representation of retFromThread

    for (int i = 0; i < NUM_OF_THREADS; i++){
        pthread_join(myThreads[i], (void **)&retFromThread);                                 // Wait for the thread to terminate and get the return value from it

        intRCThread = *(int *)retFromThread;
        printf("Outside thread, which returned %d\n", intRCThread);
    }

    printf("After the threads finished, localNum is: %d\n", localNum);

    // return 0;
}
