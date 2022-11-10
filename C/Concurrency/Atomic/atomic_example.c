#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define NUM_OF_THREADS 10

//Specify two types of counter: atomic and non-atomic
atomic_int atomicCounter;
int nonAtomicCounter;

void *threadFunc(void *thr_data)
{
    for (int n = 0; n < 1000; ++n){
        nonAtomicCounter++;
        atomicCounter++;
        // for this example, relaxed memory order is sufficient, e.g.
        // atomic_fetch_add_explicit(&atomicCounter, 1, memory_order_relaxed);
    }
    return 0;
}
int main(int argc, char const **argv)
{
    pthread_t threadsIDs[NUM_OF_THREADS];

    for (int i = 0; i < NUM_OF_THREADS; ++i)
        pthread_create(&threadsIDs[i], NULL, threadFunc, NULL);
    for (int i = 0; i < NUM_OF_THREADS; ++i)
        pthread_join(threadsIDs[i], NULL);

    printf("The atomic counter is %u\n", atomicCounter);                    // Must always be 10000
    printf("The non-atomic counter is %u\n", nonAtomicCounter);             // Most likely, will not be 10000

    return 0;
}