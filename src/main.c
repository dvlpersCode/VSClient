//
// Created by Cedric on 30.11.2017.
//
#define _WIN32_WINNT 0x0501

#include <stdio.h>
//#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>

void initializeCharArray(char *);
int getUserInput();
int readNumberFromTerminal();
void readFileNames(char *);
void appendToFileString(char *, char *);
char *readNumberOfBytes();
void readFiles(char *);
void serverConnection(const char *);

const char READ_BYTE_NUMBER[] = "Wie viele Bytes wollen Sie von dem Server erhalten (n <= 10): \n n = ";
const char READ_NUMBER_OF_FILES[] = "Wie viele Dateinamen wollen Sie an den Server senden? \n Anzahl: ";
const char READ_FILE_NAME[] = "Lese Dateiname: ";

/**
 * main function of the program
 * @return 0 = success, >0 = failed
 */
int main() {
    getUserInput();
    return 0;
}

int getUserInput() {
    int exit = 0;
    char byteNumberAsChar[3];
    char fileNamesString[250];

    memset(fileNamesString, '\0', sizeof(fileNamesString));

    while (exit == 0) {
        //initialize the char array
        initializeCharArray(fileNamesString);

        //read number of bytes that the user wants to receive from the server and copy the result to byteNumbersAsChar
        strcpy(byteNumberAsChar, readNumberOfBytes());

        //append the char array to the fileNamesString
        appendToFileString(fileNamesString, byteNumberAsChar);

        readFiles(fileNamesString);

        serverConnection(fileNamesString);

        exit = 1;
    }
}

/**
 * initialize a array with '\0'
 * @param array
 */
void initializeCharArray(char *array) {
    memset(&array, '\0', sizeof(array));
}

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

        //conver the number to a char array
        numberOfBytes = strtol(byteNumberAsChar, &pointer, 10);
    } while (numberOfBytes == 0);
    returnNumber = byteNumberAsChar;
    return returnNumber;
}

void readFiles(char *fileNamesString) {
    int numberOfFiles = 0;

    //read how many files the user wants to send to the server
    printf(READ_NUMBER_OF_FILES);
    numberOfFiles = readNumberFromTerminal();

    while (numberOfFiles > 0) {
        //read a file name and append it to fileNamesString
        readFileNames(fileNamesString);
        numberOfFiles--;
    }
}

int readNumberFromTerminal() {
    int number = 0;
    char numberAsChar[2];
    char *pointer;

    scanf("%s", numberAsChar);
    number = strtol(numberAsChar, &pointer, 10);
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

void serverConnection(const char *stringFilesNames) {
    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        printf("Fehler beim erstellen des Socket");
    }

    struct sockaddr_in serveraddr;  /* Struktur fuer die Clientadresse */

    serveraddr.sin_family = AF_INET;             /* Familie auf Internet setzen */
    serveraddr.sin_port = htons(5193);  /* host-byte-order -> network byte-order */
    serveraddr.sin_addr.s_addr = INADDR_ANY;     /* Lokale IP-Adressen setzen */

    int status = connect(sock, (struct sockaddr *) &serveraddr, sizeof(serveraddr));

    if (status == -1) {
        printf("Fehler beim Verbinden zum server");
    }
}