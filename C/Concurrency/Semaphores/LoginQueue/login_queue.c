#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Define constants
#define NUM_OF_USERS                16
#define MAX_NUM_OF_USERS_LOGGED_ON  12

// Define synchronization variables
sem_t semLogin;

void *loginProcessor(void *arg)
{
    printf("(%llu) Waiting in the login queue\n", pthread_self());
    sleep(1);                                                                       // wait a second to see that all the threads came here

    sem_wait(&semLogin);
    printf("(%llu) Logged IN\n", pthread_self());
    sleep(rand() % 5 + 1);                                                          // As if a user making some work and the unlogon
    printf("(%llu) Logged OUT\n", pthread_self());
    sem_post(&semLogin);

    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t usersThreads[NUM_OF_USERS];

    // 0. Initialize semaphores, mutex and conditional variables
    sem_init(&semLogin, 0, 0);
    sem_init(&semLogin, 0, MAX_NUM_OF_USERS_LOGGED_ON);

    // 1. Create threads sequentially
    for (int i = 0; i < NUM_OF_USERS; i++)
        pthread_create(&usersThreads[i], NULL, loginProcessor, NULL);

    // 2. Wait for the Producers threads to finish
    for (int i = 0; i < NUM_OF_USERS; i++)
        pthread_join(usersThreads[i], NULL);
    printf("==> Right after all the users logged on\n");
    // No waiting for the consumers:the processing: %d\n", numOfItemsInBuffer);

    sem_destroy(&semLogin);

    return 0;
}