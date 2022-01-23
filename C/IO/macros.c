#include "stdio.h"
#include "math.h"
#include "assert.h"
#include "stdbool.h"
#include "string.h"
int lane(void);

#define CONSTANTO 25
#define SPACE ' '
#define PS() printf("%c", SPACE)
#define BIG(X) 3 + (X)
#define SIMSQ(X, Y) ((X*X)+(Y*Y))
#define PRINT(X) printf("Value of " #X " is %d. Its address is %8p", X, (void *)&X)

#define ISBOOL(X) _Generic((X), _Bool: 1, default: 0) ? "boolean" : "not boolean"
#define ISBOOL_PRINT(X) _Generic((X), _Bool: 1, default: 0) ? puts("boolean") : puts("not boolean")
int main(int argc, char const *argv[])
{

    /* _Generic macro test */
    char * boolSign;
    _Bool boolValue;
    char Char;
    boolSign = ISBOOL(boolValue);
    boolSign = ISBOOL(Char);
    ISBOOL_PRINT(boolValue);
    ISBOOL_PRINT(Char);


    printf("Current date: %s \n", __DATE__);
    printf("Current file: %s \n", __FILE__);
    printf("Line in the file: %d \n", __LINE__);
    printf("Standard: %d \n", __STDC__);
    printf("Standard hosted: %d \n", __STDC_HOSTED__);
    printf("Standard version: %ld \n", __STDC_VERSION__);
    printf("Current date: %s \n", __TIME__);

    int test = lane();

    PRINT(test);

    /* assert() macro testing */
    double x, y, z;
    puts("Enter a pair of numbers (0 0 to quit): ");
    while (scanf("%lf%lf", &x, &y) == 2 && (x != 0 || y != 0))
    {
        z = x * x - y * y; /* should be + */
        assert(z >= 0);
        printf("answer is %f\n", sqrt(z));
        puts("Next pair of numbers: ");
    }

    return 0;
}

int lane(void){
    printf("Function is: %s\n", __func__);
    return 0;
}

void copyArrays(){
    double array1[100];
    double array2[300];
    memcpy(array1, array2, 100 * sizeof(double));
    memcpy(array1, array2 + 200, 100 * sizeof(double));
}
