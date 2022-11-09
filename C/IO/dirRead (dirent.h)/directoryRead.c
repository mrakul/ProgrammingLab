#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
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

    /*** Read stdin symbol-by-symbol ***/
    // while (((readChar = getchar()) != '\n') &&
    //        readChar != EOF)
    // {
    //     printf("Input char is: %c\n", readChar);
    // }
    FILE *file1;
    if ((file1 = fopen(".\\C\\dirRead\\file.txt", "r")) == NULL)
    {
        printf("Cannot open file.\n");
        exit(1);
    }

    // readChar = getchar();
    // putchar('\n');
    // putchar('\n');
    //const size_t LINE_SIZE = 40;

    //enum NUMBERS {ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FOURTY = 40};
    //char line[FOURTY] = {0};
    size_t lineLength = 20;
    char line[atoi(argv[2])]; //variable-length set by arguments passed by main arguments (argv2)
    char line2[lineLength];
    printf("Line1 size is: %zu\n", sizeof(line));
    printf("Line2 size is: %zu\n", sizeof(line2));
    printf("size-t type size is: %zu\n", sizeof(size_t));
    printf("lineLength size is: %zu\n", sizeof(lineLength));
    while (feof(file1) == 0)
    {
        if (fgets(line, *argv[2], file1) != NULL)
            printf("%s", line);
    }
    fputc('\n', stdout);                // Print "\n" after the last line

    if (fclose(file1) == 0)
    {
        printf("File is closed successfully");
    }

    int *intPtr = malloc(sizeof(*intPtr) * 70);
    intPtr[0] = 10;
    free(intPtr);

    return 0;
}
