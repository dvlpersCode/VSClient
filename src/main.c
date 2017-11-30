//
// Created by Cedric on 30.11.2017.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

void initializeCharArray(char *);
int getUserInput();
int readNumberFromTerminal();
void readFileNames(char *);

int main() {
    getUserInput();
    return 0;
}

int getUserInput() {
    int numberOfBytes = 0;
    int numberOfFiles = 0;
    int exit = 0;
    char byteNumberAsChar[2];
    char fileNamesString[250];

    memset(fileNamesString, '\0', sizeof(fileNamesString));

    while (exit == 0) {
        //initialize the char array
        initializeCharArray(fileNamesString);
        printf("Wie viele Bytes wollen Sie von dem Server erhalten (n <= 10): \n n = ");

        //read a number from the terminal
        numberOfBytes = readNumberFromTerminal();

        //conver the number to a char array
        snprintf(byteNumberAsChar, 4, "%d", numberOfBytes);

        //append the char array to the fileNamesString
        strcat(fileNamesString, "-");
        strcat(fileNamesString, byteNumberAsChar);

        //read how many files the user wants to send to the server
        printf("Wie viele Dateinamen wollen Sie an den Server senden? \n Anzahl: ");
        numberOfFiles = readNumberFromTerminal();

        while (numberOfFiles > 0) {
            //read a file name and append it to fileNamesString
            readFileNames(fileNamesString);
            numberOfFiles--;
        }

        printf("N: %d, Files: %d", numberOfBytes, numberOfFiles);
        exit = 1;
    }

}

void initializeCharArray(char *array) {
    memset(&array, '\0', sizeof(array));
}

int readNumberFromTerminal() {
    int number = 0;

    scanf("%d", &number);
    return number;
}

void readFileNames(char *fileString) {
    char fileName[47];
    printf("Lese Dateiname: ");
    scanf("%s", fileName);
    strcat(fileString, " -");
    strcat(fileString, fileName);
    printf("\n%s\n", fileString);
}


