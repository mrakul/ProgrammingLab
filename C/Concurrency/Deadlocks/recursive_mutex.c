#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_OF_CARS 0
#define NUM_OF_FILLERS 8
#define FUEL_PORTION 50

pthread_mutex_t mutexFuel = 50;
pthread_mutex_t recursiveMutex;
pthread_mutexattr_t mutexRecursiveAttributes;
int fuelLevel = 50;

void *fillGasStation(void *arg)
{
    pthread_mutex_lock(&recursiveMutex);                                        // (!) If lock the recursive mutex several times ...
    pthread_mutex_lock(&recursiveMutex);
    // pthread_mutex_lock(&mutexFuel);                                          // If work with non-recursive mutex, this leads to deadlock
    // pthread_mutex_lock(&mutexFuel);
    printf("Fuil is being filled by %llu thread", pthread_self());
    sleep(1);                                                                   // Just to see delay between threads (for example, if only one filling input, but they are doing some work excepting filling, before locking the mutex)

    fuelLevel += FUEL_PORTION;
    printf("==> Fuel was filled: %d\n", fuelLevel);
    pthread_mutex_unlock(&recursiveMutex);
    pthread_mutex_unlock(&recursiveMutex);                                      // ... then mutex should be unlocked the same number of times

    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t threadFiller[NUM_OF_FILLERS];

    pthread_mutex_init(&mutexFuel, NULL);
    //recursive mutex example
    pthread_mutexattr_init(&mutexRecursiveAttributes);
    pthread_mutexattr_settype(&mutexRecursiveAttributes, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&recursiveMutex, &mutexRecursiveAttributes);

    // Create fillers
    for (int i = 0; i < NUM_OF_FILLERS; i++)
        pthread_create(&threadFiller[i], NULL, &fillGasStation, NULL);

    // Join the threads
    for (int i = 0; i < NUM_OF_FILLERS; i++)
        pthread_join(threadFiller[i], NULL);

    // Destroy mutex and cond variable
    pthread_mutex_destroy(&mutexFuel);
    pthread_mutex_destroy(&recursiveMutex);
    pthread_mutexattr_destroy(&mutexRecursiveAttributes);

    return 0;
}
