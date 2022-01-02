#include "fibFunctions.h"

int fibByLoop(int n){
    int oneBefore = ONE;      //the first number is 1 initially
    int twoBefore = ONE;      //the second number is 1 initially
    int isSwitchNum = 0;    //the first accumulates first
    int currentIndex = 3;   //start loop from the 3-rd number

    if (n < 3)
        return 1;
    while (currentIndex <= n){
    /* If the first or the second number */
        if (!isSwitchNum)
            oneBefore = oneBefore + twoBefore;
        else
            twoBefore = oneBefore + twoBefore;

    isSwitchNum = !isSwitchNum; //switch to accumulate 1-st / 2-nd
    currentIndex++;
    }

    return (isSwitchNum ? oneBefore : twoBefore);
}

int fibByRecursion (int n){
    if (n < 3)
        return 1;
    else
        return fibByRecursion(n - 1) + fibByRecursion(n-2);
}