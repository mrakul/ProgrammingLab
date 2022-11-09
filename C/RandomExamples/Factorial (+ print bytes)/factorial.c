#include <stdio.h>
#include <stdint.h>

void test(int *var);
int factorial(int);

int main(int argc, const char **argv){
    uint32_t number;
    printf("Please, input the number to have its factorial: ");
    scanf("%u", &number);
    printf("Factorial of %d is ", number);
    printf("%d\n", factorial(number));
    putchar('\n');

    /*** Output value byte-by-byte ***/
    char *ch;
    printf("number address: %p\n", (void *)&number);
    printf("number's address + 1 byte: %p\n", (char *)&number + 1);     //first - get the address-of(number) as address to uint32_t, then - cast to (char *), then - add 1 as sizeof(char)
    printf("number's address + sizezof(number): %p\n", (char *)(&number + 1)); //first - get the address-of(number) as address to uint_32_t, then - add sizeof(uint32_t) to the address, then - cast to (char *)
    //Set ch to the last byte of 'number'
    ch = (char *)&number + sizeof(number) - 1;

    int i = sizeof(number);
    number = 1025;
    while (i-- > 0){
        printf("%02hhX ", *ch);
        ch--;
    } putchar('\n');

    /*** Cast test ***/
    uint32_t number2 = -5;
    printf("Number2 value as unsigned %u\n", number2);
    printf("Number2 value as signed%d\n", (int)number2);

    /*** Test #2 ***/
    float variable = 2.5f;
    float *varPtr = &variable;
    printf("Variable value is: %f\n", *varPtr);

    //Consider variable memory as int
    test((int *)varPtr);
    printf("Variable after setting: %f\n", *varPtr);
    printf("Value with casting to int: %d\n", (int)*varPtr);  //first - dereferencing, then - casting?
    printf("Value with casting pointer to int %d\n", *(int *)varPtr); //first - casting to (int *), then - dereferencing as int?
    /*** End cast test ***/

    getchar();
    getchar();
}

int factorial(int n){
    if (n > 0)
        return n * factorial(n - 1);
    else
        return 1;
}

void test(int *var){
    *var = 1104838975;
}