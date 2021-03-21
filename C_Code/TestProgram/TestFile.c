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
    char srcString[] = "Test string";
    const char * srcString2 = "Test string 2";
    const char * srcString3[] = {"Test string 3"};

    char destString1[20];
    char * destString2[20];

    char charToEnd;
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
    printf("1-st string value: %s\n", srcString);     // Implicit cast to a pointer to the array's first element
    printf("1-st string value: %s\n", &srcString);    // First exception above: address-of is taken from array of elements
    printf("1-st string value: %s\n", &srcString[0]); // Address of the first element

    printf("2-st string value: %s\n", srcString2);
    printf("2-st string value: %s\n", &srcString2);
    printf("2-st string value: %s\n", &srcString2[0]);

    printf("3-rd string value: %s\n", srcString3);
    printf("3-rd string value: %s\n", &srcString3);
    printf("3-rd string value: %s\n", srcString3[0]);
  
    printf("Size of src1: %d\n"
           "Size of src2: %d\n",
           "Size of src3: %d\n",
           sizeof(srcString),     // Size of the entire array = 12, exception 2 from the description above
           sizeof(srcString2),    // Size of the pointer                     
           sizeof(srcString3));

    strcpy(destString1,srcString);
    printf("New string value: %s", destString2);

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

    DIR *dir1;
    struct dirent *dirEntry;
    dir1 = opendir(".");
    if (dir1)
    {
        while ((dirEntry = readdir(dir1)) != NULL)
        {
            printf("%s\n", dirEntry->d_name);
        }
        closedir(dir1);
    }

    getchar();
}

void function1(int * const val1)
{
    *val1 = 7;
}