#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char const *argv[]){
    int ch;
    int wordCounter, letterCounter;
    wordCounter = letterCounter = 0;
    bool wordStarted = false;


    printf("Please, input the string: \n");
    while ((ch = getchar()) != EOF && ch != '\n')
    {
        if (isalnum(ch)) {
            if (!wordStarted)
                wordStarted = true;
            letterCounter++;
            putchar(ch);
        }
        else if (isspace(ch) || ispunct(ch)) {
            if (wordStarted) {
                wordStarted = false;
                wordCounter++;

            }
        }
    }

    putchar('\n');
    if (wordStarted)
        wordCounter++;

    printf("Number of words: %d\n", wordCounter);
    printf("Number of letters: %d\n", letterCounter);
    printf("Average letters: %05.2f\n", (float)letterCounter/wordCounter);

    return 0;
}