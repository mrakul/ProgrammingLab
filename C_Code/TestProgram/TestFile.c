#include <stdio.h>
#include <string.h>
#include "timeTest.h"

void function1(int *const val1);

struct Human
{
    int cash;
} man1 = {7}, *p_man1;

int main(int argc, char const *argv[])
{
    char srcString[] = "Test string";
    const char *srcString2 = "Test string 2";
    const char *srcString3[] = {"Test string 3"};

    char destString1[20];
    const char *destString2 = "destString2 initial value"; // test that the copy is restricted. Without const - error arised

    int a, i;
    p_man1 = &man1;

    // Example:
    //     char s[] = "hello";
    //     char *p = "world";
    //     printf("%s, %s\n", s, p);
    // It looks like you're passing an array for the first %s and a pointer for the second,
    // but in fact you're (correctly) passing pointers for both.
    // In C, any expression of array type is implicitly converted to a pointer to the array's
    // first element unless it's in one of the following three contexts:
    //  - It's an argument to the unary "&" (address-of) operator
    //  - It's an argument to the unary "sizeof" operator
    //  - It's a string literal in an initializer used to initialize an array object.
    printf("1-st string value: %s\n", srcString);          // Implicit cast to a pointer to the array's first element
    printf("1-st string value: %s\n", (char *)&srcString); // First exception above: address-of is taken from array of elements, then need to cast to (char*)
    printf("1-st string value: %s\n", &(srcString[0]));    // Address of the first element

    printf("2-st string value: %s\n", srcString2);
    printf("2-st string value: %s\n", (char *)&srcString2); // Need to cast to (char*)
    printf("2-st string value: %s\n", &srcString2[0]);

    //printf("3-rd string value: %s\n", srcString3);
    //printf("3-rd string value: %s\n", &srcString3);
    printf("3-rd string value: %s\n", srcString3[0]);

    printf("Size of src1: %zu\n"
           "Size of src2: %zu\n"
           "Size of src3: %zu\n",
           sizeof(srcString),  // Size of the entire array = 12, exception 2 from the description above
           sizeof(srcString2), // Size of the pointer
           sizeof(srcString3));

    strcpy(destString1, srcString);
    // strcpy(destString2, srcString2); // restricted, since destString2 is const char * pointer (and point to read only memory)
    printf("New string value: %s\n", destString2);

    for (i = 0; i < 10; i++)
    {
        p_man1->cash++;
        printf("Man's cash increased: %d\n", p_man1->cash);
    }
    if (p_man1->cash > 15)
    {
        printf("Enough money!\n");
    }
    else
    {
        function1(&a);
        printf("Money is not enough :(\n");
    }

    for (i = 1; i < argc; i++)
    {
        printf("Argument %d value is %s\n"
               "And its length is: %zu\n",
               i, argv[i], strnlen(argv[i], 15));
    }

    timeTest();
    getchar();

    gets(destString1);
}

void function1(int *const val1)
{
    *val1 = 7;
}