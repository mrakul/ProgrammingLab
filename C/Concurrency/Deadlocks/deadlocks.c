#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_OF_CARS 0
#define NUM_OF_FILLERS 8
#define NUM_OF_FILLING_CYCLES 5
#define FUEL_PORTION 50
#define WATER_PORTION 50
#define CAR_TANK_CAPACITY 40

pthread_mutex_t mutexFuel = 50;
pthread_mutex_t mutexWater = 50;
int fuelLevel = 50;
int waterLevel = 50;

void *fillGasStation(void *arg)
{
    if (pthread_self() & 1){                                    // Odd threads lock mutexFuel first
        pthread_mutex_lock(&mutexFuel);
        pthread_mutex_lock(&mutexWater);                        // Here, one thread takes mutexFuel and tries to lock the mutexWater...
    }
    else{                                                       // Even threads lock mutexWater first
        pthread_mutex_lock(&mutexWater);
        pthread_mutex_lock(&mutexFuel);                         // Here, another thread takes mutexWater and tries to lock the mutexFuel, so the threads are locked by each other
    }
    // Note: non-recursive mutex can result in a deadlock if just lock the mutex sequentially in one thread
    fuelLevel += FUEL_PORTION;
    waterLevel += WATER_PORTION;
    printf("==> Fuel was filled: %d\n", fuelLevel);
    printf("==> Water was filled: %d\n", waterLevel);

    pthread_mutex_unlock(&mutexFuel);
    pthread_mutex_unlock(&mutexWater);

    sleep(1);
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t threadFiller[NUM_OF_FILLERS];
    //pthread_t threadCars[NUM_OF_CARS];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_mutex_init(&mutexWater, NULL);

    // Create fillers
    for (int i = 0; i < NUM_OF_FILLERS; i++)
        pthread_create(&threadFiller[i], NULL, &fillGasStation, NULL);

    // Join the threads
    for (int i = 0; i < NUM_OF_FILLERS; i++)
        pthread_join(threadFiller[i], NULL);

    // Destroy mutex and cond variable
    pthread_mutex_destroy(&mutexFuel);
    pthread_mutex_destroy(&mutexWater);

    return 0;
}
