/**
 * Cedric Schreiner, Florian Hennrich, Nicolas Loosen, Mesut Özcan, Robin Tauer, Alexander Lukacs
 * Class to implement a client programm to send a number of Filenames and receive the first n bytes
 * of each file
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>

void initializeCharArray(char *);
void getUserInput();
int readNumberFromTerminal();
void readFileNames(char *);
void appendToFileString(char *, char *);
char *readNumberOfBytes();
int readFiles(char *);
void serverConnection(const char *, int);


const int port = 5193;
const char READ_BYTE_NUMBER[] = "Wie viele Bytes wollen Sie von dem Server erhalten (n <= 10): \n n = ";
const char READ_NUMBER_OF_FILES[] = "Wie viele Dateinamen wollen Sie an den Server senden? \n Anzahl: ";
const char READ_FILE_NAME[] = "Lese Dateiname: ";
const char CREATE_SOCKET_ERROR[] = "Fehler beim erstellen des Socket";
const char CONNECTION_ERROR[] = "Fehler beim Verbinden zum server";

/**
 * main function of the program
 * @return 0 = success, >0 = failed
 */
int main() {
    getUserInput();
    return 0;
}

/**
 * execute all methods which are necessaray to send and receive data to/from a server
 */
void getUserInput() {
    int exit = 0;
    int numberOfFiles = 0;
    char byteNumberAsChar[3];
    char fileNamesString[250];

    while (exit == 0) {
        //initialize the char array
        initializeCharArray(fileNamesString);

        //read number of bytes that the user wants to receive from the server and copy the result to byteNumbersAsChar
        strcpy(byteNumberAsChar, readNumberOfBytes());

        //append the char array to the fileNamesString
        appendToFileString(fileNamesString, byteNumberAsChar);

        numberOfFiles = readFiles(fileNamesString);

        serverConnection(fileNamesString, numberOfFiles);

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
 * create full string
 * @param fileString
 * @param stringToAppend
 */
void appendToFileString(char *fileString, char *stringToAppend) {
    strcat(fileString, " -");
    strcat(fileString, stringToAppend);
}

/**
 * connect to server, send dataString, wait and receive Data from Server
 * @param stringFilesNames
 * @param numberOfFiles
 */
void serverConnection(const char *stringFilesNames, int numberOfFiles) {
    SOCKET sock;
    char receivedData[100];
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        printf(CREATE_SOCKET_ERROR);
        exit(1);
    }

    struct sockaddr_in serveraddr;  /* Struktur fuer die Serveradresse */

    serveraddr.sin_family = AF_INET;             /* Familie auf Internet setzen */
    serveraddr.sin_port = htons(port);  /* host-byte-order -> network byte-order */
    serveraddr.sin_addr.s_addr = INADDR_ANY;     /* Lokale IP-Adressen setzen */

    //try to connect to the server
    int status = connect(sock, (struct sockaddr *) &serveraddr, sizeof(serveraddr));

    if (status == -1) {
        printf(CONNECTION_ERROR);
        exit(2);
    }

    //send data to server
    send(sock, stringFilesNames, sizeof(*stringFilesNames), 0);

    //receive data from server
    for (int i = 0; i < numberOfFiles; i++) {
        initializeCharArray(receivedData);
        if (recv(sock, receivedData, 100, MSG_PEEK) < 0) {
            printf("Fehler beim empfangen der Daten");
        } else {
            printf("Daten erhalten: %s", receivedData);
        }
    }
}