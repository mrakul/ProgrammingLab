#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char readChar;
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
    if ((file1 = fopen(".\\C_Code\\TestProgram\\file.txt", "r")) == NULL)
    {
        printf("Cannot open file.\n");
        exit(1);
    }

    // readChar = getchar();
    // putchar('\n');
    // putchar('\n');
    //const size_t LINE_SIZE = 40;

    enum NUMBERS {ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FOURTY = 40};
    size_t lineLength = 20;
    char line[FOURTY] = {0};
    int line2[lineLength];
    printf("Line1 size is: %d\n", sizeof(line));
    printf("Line2 size is: %d\n", sizeof(line2));
    while (feof(file1) == 0)
    {
        if (fgets(line, FOURTY, file1) != NULL)
        {
            printf("%s", line);
        }
    }

    if (fclose(file1) == 0)
    {
        printf("File is closed successfully");
    }

    return 0;
}
