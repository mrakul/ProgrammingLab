#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;

#define NUM_OF_FILLING_CYCLES 5
#define NUM_OF_CARS 4
#define FUEL_PORTION 60
#define CAR_TANK_CAPACITY 40

int fuelLevel = 0;

void *fillGasStation(void *arg)
{
    for (int i = 0; i < NUM_OF_FILLING_CYCLES; i++){
        pthread_mutex_lock(&mutexFuel);
        fuelLevel += FUEL_PORTION;
        printf("==> Fuel was filled: %d\n", fuelLevel);
        pthread_cond_broadcast(&condFuel);                           // Here, all the car threads are awake. Note: this may be in or out of the mutex locked. However, if predictable scheduling behavior is required, then the mutex shall be locked by the thread
        printf(">>> BROADCASTING <<<\n");                            // Other threads are not starting until this thread release the mutex
        pthread_mutex_unlock(&mutexFuel);
        sleep(1);
    }
    return NULL;
}

void *fillCar(void *arg)
{
    pthread_mutex_lock(&mutexFuel);
    while (fuelLevel < CAR_TANK_CAPACITY){
        printf("No fuel in the gas station. Waiting ...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);                   // This atomically locks the current thread on the condition variable AND unlocks the mutex for the consumers
        // pthread_cond_wait() is equivalent to:
        // 1. pthread_mutex_unlock();
        // 2. wait for signal on condFuel
        // (!) 3. pthread_mutex_lock(): "The thread(s) that are unblocked shall contend for the mutex according to the scheduling policy (if applicable), and as if each had called pthread_mutex_lock()."
        printf("A car thread is unclocked... \n");
    }
    fuelLevel -= CAR_TANK_CAPACITY;
    printf("A car got the fuel. Now left: %d\n", fuelLevel);
    pthread_mutex_unlock(&mutexFuel);

    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t threadFiller;
    pthread_t threadCars[NUM_OF_CARS];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);

    // Create several cars to fill AND one filler
    for (int i = 0; i < NUM_OF_CARS; i++)
        pthread_create(&threadCars[i], NULL, &fillCar, NULL);
    pthread_create(&threadFiller, NULL, &fillGasStation, NULL);

    // Joing the threads
    pthread_join(threadFiller, NULL);
    for (int i = 0; i < NUM_OF_CARS; i++)
        pthread_join(threadCars[i], NULL);

    // Destroy mutex and cond variable
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);

    return 0;
}
