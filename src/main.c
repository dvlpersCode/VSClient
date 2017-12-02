//
// Created by Cedric on 30.11.2017.
//

#include <stdio.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

void initializeCharArray(char *);
int getUserInput();
int readNumberFromTerminal();
void readFileNames(char *);
void appendToFileString(char *, char *);

const char READ_BYTE_NUMBER[] = "Wie viele Bytes wollen Sie von dem Server erhalten (n <= 10): \n n = ";
const char READ_NUMBER_OF_FILES[] = "Wie viele Dateinamen wollen Sie an den Server senden? \n Anzahl: ";
const char READ_FILE_NAME[] = "Lese Dateiname: ";

int main() {
    getUserInput();
    return 0;
}

int getUserInput() {
    long numberOfBytes = 0;
    int numberOfFiles = 0;
    int exit = 0;
    char byteNumberAsChar[2];
    char fileNamesString[250];
    char *pointer;

    memset(fileNamesString, '\0', sizeof(fileNamesString));

    while (exit == 0) {
        //initialize the char array
        initializeCharArray(fileNamesString);
        printf(READ_BYTE_NUMBER);

        //read a number from the terminal
        scanf("%s", byteNumberAsChar);

        //conver the number to a char array
        numberOfBytes = strtol(byteNumberAsChar, &pointer, 10);

        //append the char array to the fileNamesString
        appendToFileString(fileNamesString, byteNumberAsChar);

        //read how many files the user wants to send to the server
        printf(READ_NUMBER_OF_FILES);
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
    printf(READ_FILE_NAME);
    scanf("%s", fileName);
    appendToFileString(fileString, fileName);
    printf("\n%s\n", fileString);
}

void appendToFileString(char *fileString, char *stringToAppend) {
    strcat(fileString, " -");
    strcat(fileString, stringToAppend);
}


