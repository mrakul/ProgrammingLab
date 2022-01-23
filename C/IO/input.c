#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "dirent.h"

#define MAXPATH 1023

int main(int argc, const char * argv[]){
    char buffer[80]; //buffer to read input data
    float curValue;
    //float sum = 0;
    FILE * fileToRead;

    //Get current working directory
    char workDir[MAXPATH];
    getcwd(workDir, MAXPATH);

    //Build the path to the file
    char pathToFile[MAXPATH] = {0};
    strcat(strcat(strcpy(pathToFile, workDir), "\\"), argv[1]);

    if (argc > 2){
        printf("Too much arguments! Please, input zero or one argument \n");
        exit(EXIT_FAILURE);
    }

    if (argc == 0)      //no arguments: read from stdin
        //TODO:
        fgets(buffer, sizeof(buffer), stdin);
    else {              //read from the file of the argument
        fileToRead = fopen(pathToFile, "r");
        if (fileToRead == NULL){
            printf("The flie couldn't be opened. \n");
            exit(EXIT_FAILURE);
        }
        else{
            while (!feof(fileToRead)){
                fscanf(fileToRead, "%5f", &curValue);
                printf("Current value is: %5.2f\n", curValue);
            }
        fclose(fileToRead);
        }
    }

    return 0;
}