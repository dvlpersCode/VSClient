//
// Created by Cedric on 06.12.2017.
//

#include <stdio.h>
#include <stdlib.h>
#include "ClientInput.h"
#include "StringUtillities.h"

/**
 * ask the user how many bytes he wants to receive from the server of each file
 * @return the number of bytes as char pointer
 */
char *readNumberOfBytes() {
    char byteNumberAsChar[3];
    char *returnNumber;
    char *pointer;
    long numberOfBytes = 0;

    do {
        printf(READ_BYTE_NUMBER);

        //read a number from the terminal
        scanf("%s", byteNumberAsChar);
        byteNumberAsChar[2] = '\0';

        //convert the number to a char array
        numberOfBytes = strtol(byteNumberAsChar, &pointer, 10);
    } while (numberOfBytes == 0);
    returnNumber = byteNumberAsChar;
    return returnNumber;
}

/**
 * read numberOfFiles and and the file Names
 * @param fileNamesString
 * @return
 */
int readFiles(char *fileNamesString) {
    int numberOfFiles = 0;

    //read how many files the user wants to send to the server
    printf(READ_NUMBER_OF_FILES);
    numberOfFiles = readNumberFromTerminal();

    for (int i = 0; i < numberOfFiles; i++) {
        readFileNames(fileNamesString);
    }
    return numberOfFiles;
}

/**
 * reads the User Input from the terminal
 * @param fileString
 */
void readFileNames(char *fileString) {
    char fileName[47];
    printf(READ_FILE_NAME);
    scanf("%s", fileName);
    appendToFileString(fileString, fileName);
    printf("\n%s\n", fileString);
}

/**
 * initialize an number from the terminal
 * @return
 */
int readNumberFromTerminal() {
    int number = 0;
    char numberAsChar[2];
    char *pointer;

    scanf("%s", numberAsChar);
    number = strtol(numberAsChar, &pointer, 10);
    return number;
}

