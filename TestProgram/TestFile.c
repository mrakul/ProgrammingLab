#include <stdio.h>
#include <string.h>
#include "timeTest.h"

void function1(int * const val1);

struct Human
{
    int cash;
} man1 = {7}, *p_man1;

int main(int argc, char const *argv[])
{   
    char charToEnd;
    int a, i;
    p_man1 = &man1;

    for (i = 0; i < 10; i++)
    {
        p_man1->cash++;
        printf("Man's cash increased: %d\n", p_man1->cash);
    }
    if (p_man1->cash > 15){
        printf("Enough money!\n");
    }
    else{
        function1(&a);
        printf("Money is not enough :(\n");
    }

    for (i = 1; i < argc; i++)
    {
        printf("Argument %d value is %s\n"
               "And its length is: %d\n", i, argv[i], strnlen(argv[i],15));
    }

    timeTest();

    fgets(&charToEnd, 1, stdin);
}

void function1(int * const val1)
{
    *val1 = 7;
}