#include "fibFunctions.h"

int fibByLoop(int fibNum)
{
    int oneBefore = ONE;  // the first number is 1 initially
    int twoBefore = ONE;  // the second number is 1 initially
    int isSwitchNum = 0;  // 0 - next accumulates the oneBefore, 1 - next accumulates the twoBefore

    if (fibNum < 3)       //1-st and 2-nd are always 1
        return 1;
    else
        //Start loop from the 3-rd number; till the required number reached; switch accumulator of the number
        for (int currentIndex = 3; currentIndex <= fibNum; isSwitchNum = !isSwitchNum, currentIndex++)
        {
            /* If the first or the second number */
            if (!isSwitchNum)
                oneBefore = oneBefore + twoBefore;
            else
                twoBefore = oneBefore + twoBefore;
        }

    return (isSwitchNum ? oneBefore : twoBefore);      //If next should be twoBefore, means that the last accumulated by oneBefore. Otherwise, return twoBefore
}

int fibByRecursion(int fibNum)
{
    if (fibNum < 3)
        return 1;
    else
        return fibByRecursion(fibNum - 1) + fibByRecursion(fibNum - 2);
}