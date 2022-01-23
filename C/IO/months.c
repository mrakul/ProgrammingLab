#include "stdio.h"
#include "stdlib.h"

struct monthData_s
{
    char monthName[10];
    char monthAbbr[3];
    int monthDays;
    int monthNum;
};

enum answers {yes, no, maybe};

struct monthData_s year[12] =
    {
        {"January", "JAN", 31, 1},
        {"February", "FEB", 28, 2},
        {"March", "MAR", 31, 3},
        {"May", "MAY", 31, 5},
        [3] = {"April ", "APR", 30, 4}, //designated initializer is allowed for structures (rewrites incorrect May above)
        {"May", "MAY", 31, 5},
        //   {"June", "JUN", 30, 6},
        //   {"July", "JUL", 31, 7},
        //   {"August", "AUG", 31, 8},
        //   {"September", "SEP", 30, 9},
        //   {"October", "OCT", 31, 10},
        //   {"November", "NOV", 30, 11},
        //   {"December", "DEC", 31, 12}
};

void showNumOfDays(int month);

int main(int argc, const char *argv[])
{

    char * (* ptrFunc)(char *, char); //a pointer to a function that returns a pointer-to- char
                                     // and takes a pointer-tochar and a char as arguments.
    int monthNum;
    printf("Input the month: ");
    int result;
    result = scanf("%d", &monthNum);
    char curChar;
    while ((curChar = getchar()) != '\n')
    {
        int i = 123;
    }
    putchar('\n');

    showNumOfDays(monthNum);
    return 0;
}

void showNumOfDays(int month)
{
    int daysBeforeMonth = 0;
    int i;
    for (i = 0; i < month; i++)
        daysBeforeMonth = daysBeforeMonth + year[i].monthDays;
    printf("Days before %s: %d \n", year[month].monthName, daysBeforeMonth);
}
