#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

// Define constants
#define NUM_OF_THREADS 12
#define BARRIER_LEVEL 10
#define THREAD_WON 1
#define THREAD_LOST 0

// Define synchronization variables
pthread_barrier_t barrierRolledDice;
pthread_barrier_t statusesAreFilled;

int diceValues[NUM_OF_THREADS];
int wonOrLoseStatus[NUM_OF_THREADS] = {0};

void *rollDice(void *threadArg)
{
    int index = *(int *)threadArg;
    diceValues[index] = index % 6 + 1;

    while (1){                                                                   // Make the process infinite
        pthread_barrier_wait(&barrierRolledDice);                                // Here, we want to wait until all the threads are finished with rolling dice to notify main and allow him to fill the statuses array
        pthread_barrier_wait(&statusesAreFilled);                                // And after, we are waiting until the the main fills the statuses array, so the threads may move on
        if (wonOrLoseStatus[index] == THREAD_WON)
            printf("%d rolled %d, WINNER\n", index, diceValues[index]);
        else
            printf("%d rolled %d, LOOSER \n", index, diceValues[index]);
    }
    free(threadArg);                                                                // (!) Important to free it here, not after the create_thread :)
    return NULL;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    pthread_t myThreads[NUM_OF_THREADS];

    // // 0. Initialization
    pthread_barrier_init(&barrierRolledDice, NULL, NUM_OF_THREADS + 1);             // (!) Need to consider the main thread also
    pthread_barrier_init(&statusesAreFilled, NULL, NUM_OF_THREADS + 1);             // (!) Need to consider the main thread also

    // 1. Create threads sequentially
    for (int i = 0; i < NUM_OF_THREADS; i++){
        int *argFromMain = malloc(sizeof(int));
        *argFromMain = i;
        pthread_create(&myThreads[i], NULL, rollDice, (void *)argFromMain);
    }

    // 2. Find the maximum rolled value of the threads and set the status
    // Key moment of the barriers using below
    while (1){                                                                          // Make the process infinite
        pthread_barrier_wait(&barrierRolledDice);                                       // (!) Here we are saying that all the dices were rolled
        int maxValue = 0;
        for (int i = 0; i < NUM_OF_THREADS; i++)
            if (diceValues[i] > maxValue)
                maxValue = diceValues[i];
        for (int i = 0; i < NUM_OF_THREADS; i++)
            if (diceValues[i] == maxValue)
                wonOrLoseStatus[i] = THREAD_WON;
        // Here, we allow the threads to move on and notify if they are winners or loosers
        sleep(1);
        printf("\t >>> NEW ROUND <<<\n");
        pthread_barrier_wait(&statusesAreFilled);                                       // (!) Here we are saying that the statuses are determined
    }

    // 4. Wait for the threads to finish
    for (int i = 0; i < NUM_OF_THREADS; i++)
        pthread_join(myThreads[i], NULL);
    printf("==> Right after all the Producers finished their work\n");

    // 4. Destroying
    pthread_barrier_destroy(&barrierRolledDice);
    pthread_barrier_destroy(&statusesAreFilled);

    return 0;
}