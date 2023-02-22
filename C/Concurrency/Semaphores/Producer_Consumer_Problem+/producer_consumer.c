#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
// Define constants
#define NUM_OF_ITEMS_TO_ADD 100
#define BUFFER_SIZE 10
#define NUM_OF_PRODUCERS 10
#define NUM_OF_CONSUMERS 1

// Define synchronization variables
pthread_mutex_t mutexToLock;
pthread_cond_t condVar;
sem_t semBufferIsEmpty;
sem_t semBufferIsFull;

// Define other values
int numOfItemsInBuffer = 0;
int buffer[BUFFER_SIZE] = {0};

void *producer(void *arg)
{
    for (int i = 0; i < NUM_OF_ITEMS_TO_ADD; i++){                          // This is usually while(1), data is added infinitely and undetermined
        int addedItem = rand() % 100;

        sem_wait(&semBufferIsFull);                                         // Before starting to add an item, check the semaphore if there is a pool to add to the buffer (semaphore is non-zero)

        pthread_mutex_lock(&mutexToLock);                                   // Need to lock the mutex/other threads to work with shared memory
        buffer[numOfItemsInBuffer++] = addedItem;                           // Add an item and increment the current index. Note: no need to check boundaries by using semaphores
        pthread_mutex_unlock(&mutexToLock);                                 // Unlock the mutex

        sem_post(&semBufferIsEmpty);                                        // Increment the semBufferIsEmpty, since an item was just added
    }

    return NULL;
}

void *consumer(void *arg)
{
    while (1){                                                          // Usually, consumers and producers are working in infinite loop. Note: producers are making finite work in our case

        sem_wait(&semBufferIsEmpty);                                    // Before starting to retrieve an item, check the semaphore if the buffer is empty. If so, wait when items will be added

        pthread_mutex_lock(&mutexToLock);                               // Need to lock the mutex/other threads to work with shared memory
        int retrievedItem = buffer[--numOfItemsInBuffer];               // Decrement the current index (evaluate to the previous filled) and save the item
        printf("Retrieved number: %d\n", retrievedItem);                // Item is not retrieved, that is counter is 0

        if (numOfItemsInBuffer == 0)                                    // May check or make cond_signal unconditionally: when producers finished their work, main is waiting for this signal (this condition may occur before the producers finished)
            pthread_cond_signal(&condVar);                              // Signal the waiting thread (main is waiting). If this happend before the main is waiting, then main will just pass the condition
        pthread_mutex_unlock(&mutexToLock);                             // Unlock the mutex

        sem_post(&semBufferIsFull);                                     // Increment the semBufferIsFull, since we just processed one item by the consumer
    }

    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t producerThreads[NUM_OF_PRODUCERS];
    pthread_t consumerThreads[NUM_OF_CONSUMERS];

    // 0. Initialize semaphores, mutex and conditional variables
    sem_init(&semBufferIsEmpty, 0, 0);
    sem_init(&semBufferIsFull, 0, BUFFER_SIZE);
    pthread_mutex_init(&mutexToLock, NULL);
    pthread_cond_init(&condVar, NULL);

    // 1. Create threads sequentially
    for (int i = 0; i < NUM_OF_PRODUCERS; i++)
        pthread_create(&producerThreads[i], NULL, producer, NULL);
    for (int i = 0; i < NUM_OF_CONSUMERS; i++)
        pthread_create(&consumerThreads[i], NULL, consumer, NULL);

    // 2. Wait for the Producers threads to finish
    for (int i = 0; i < NUM_OF_PRODUCERS; i++)
        pthread_join(producerThreads[i], NULL);
    printf("==> Right after all the Producers finished their work\n");
    // No waiting for the consumers:
    // for (int i = 0; i < NUM_OF_CONSUMERS; i++)
    //     pthread_join(consumerThreads[i], NULL);

    // 3. Producers finished their work. Need to check if the buffer IS empty
    pthread_mutex_lock(&mutexToLock);
    while (numOfItemsInBuffer){                                             // If this happened before the main is waiting, then main will just pass the condition with no lock by pthread_cond_wait()
        printf("==> Main thread is locked\n");                              // Consumers are stil consuming
        pthread_cond_wait(&condVar, &mutexToLock);                          // This atomically locks the current thread on the condition variable AND unlocks the mutex for the consumers
    }
    pthread_mutex_unlock(&mutexToLock);

    printf("Num of items in the buffer after the end of the processing: %d\n", numOfItemsInBuffer);

    pthread_mutex_destroy(&mutexToLock);
    sem_destroy(&semBufferIsEmpty);
    sem_destroy(&semBufferIsFull);

    return 0;
}