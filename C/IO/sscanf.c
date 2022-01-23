#include <stdio.h>

int main(void)
{
    char str[80];
    int i;
    char string[80] = "hello 1 2 3 4 5";
    sscanf(string, "%s%d", str, &i);
    printf("%s \n%d \n%s \n", str, i, string);

    int val, val2 = 0;
    char charact = '\000';
    scanf("%d %c %d", &val, &charact, &val2);
    printf("%d %c %d", val, charact, val2);

    charact = getchar();
    charact = getchar();
    return 0;
}