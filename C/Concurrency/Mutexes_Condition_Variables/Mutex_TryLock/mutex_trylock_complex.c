#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

// Define constants
#define NUM_OF_CHEFS 10
#define NUM_OF_STOVES 4
#define INIT_FUEL_LEVEL 100

// chiefs = threads of processing
// stove = shared data (+mutex)

int stoveFuelLevel[NUM_OF_STOVES] = {INIT_FUEL_LEVEL, INIT_FUEL_LEVEL, INIT_FUEL_LEVEL, INIT_FUEL_LEVEL};

// Define synchronization variables
pthread_mutex_t stoveMutex[NUM_OF_STOVES];              // For every stove

void *cookingThread(void *arg)
{
    srand(time(NULL));
    int fuelNeededToCook = (rand() % 30);
    for (int i = 0; i < NUM_OF_STOVES; i++){
        if (pthread_mutex_trylock(&stoveMutex[i]) == 0){
            if (stoveFuelLevel[i] < fuelNeededToCook){
                printf("Not enough fuel to cook in %d stove. \n", i);
            }
            else{
                stoveFuelLevel[i] -= fuelNeededToCook;
                usleep(500000);
                printf("Stove used. Fuel left in %d stove: %d\n", i, stoveFuelLevel[i]);
            }
            pthread_mutex_unlock(&stoveMutex[i]);
            break;                                                                              // Don't try another stoves after cooking
        }
        else                                                                                    // Didn't get the stove
            if (i == NUM_OF_STOVES - 1){                                                        // If all the stoves are locked, try again after delay
                usleep(300000);
                printf("Chef is waiting. Check stoves once again...\n");
                i = 0;
            }
    }

    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t myThreads[NUM_OF_CHEFS];
    // 0. Initialize mutexes
    for (int i = 0; i < NUM_OF_STOVES; i++)
        pthread_mutex_init(&stoveMutex[i], NULL);

    // 1. Create threads sequentially
    for (int i = 0; i < NUM_OF_CHEFS; i++)
        pthread_create(&myThreads[i], NULL, cookingThread, NULL);

    // 2. Wait for the threads to finish
    for (int i = 0; i < NUM_OF_CHEFS; i++)
        pthread_join(myThreads[i], NULL);

    // 3. Destroy mutexes
    for (int i = 0; i < NUM_OF_STOVES; i++)
        pthread_mutex_destroy(&stoveMutex[i]);

    return 0;
}