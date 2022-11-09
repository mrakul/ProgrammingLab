#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "fibFunctions.h"

int main(int argc, char ** argv){

    uint32_t number;
    clock_t clockBefore;
    clock_t clockAfter;
    int i = 0;

    printf("Insert the number in Fibonacci sequence: ");
    scanf("%u", &number);
    while (getchar() != '\n');

    /* Calculate Fibonacci by loop */
    clockBefore = clock();
    printf("Fibonacci value by loop: %d\n", fibByLoop(number));
    while (i++ < 99999999)
        {fibByLoop(number);}
    clockAfter = clock();
    printf("Time spent is: %f\n", (clockAfter - clockBefore)/(double)CLOCKS_PER_SEC);

    /* Calculate Fibonacci by recursion */
    i = 0;
    clockBefore = clock();
    printf("Fibonacci value by recursion: %d\n", fibByRecursion(number));
    while (i++ < 99999999)
        {fibByRecursion(number);}
    clockAfter = clock();
    printf("Time spent is: %f\n", (clockAfter - clockBefore)/(double)CLOCKS_PER_SEC);

    getchar();

    return 0;
}
