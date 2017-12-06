/**
 * Cedric Schreiner, Florian Hennrich, Nicolas Loosen, Mesut Özcan, Robin Tauer, Alexander Lukacs
 * Class to implement a client programm to send a number of Filenames and receive the first n bytes
 * of each file
 */
//--------------------includes--------------------//
#include <winsock2.h>
#include <stdio.h>
#include "ClientInput.h"
#include "StringUtillities.h"
#include "main.h"
//--------------------endincludes--------------------//

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

        connectToServer(fileNamesString, numberOfFiles);

        exit = 1;
    }
}

int connectToServer(const char* stringFileNames, int numberOfFiles){
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char serverReply[256];
    int recv_size;

    printf("\n Initialising Winsock...");
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0){
        printf("%s %d", CREATE_SOCKET_ERROR, WSAGetLastError());
        return 1;
    }
    printf("\n Initialised \n");

    //create Socket
    if((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
        printf("Could not create Socket : %d", WSAGetLastError());
    }
    printf("Socket created. \n");

    server.sin_family = AF_INET;             /* Familie auf Internet setzen */
    server.sin_port = htons(port);  /* host-byte-order -> network byte-order */
    server.sin_addr.s_addr = inet_addr("10.9.44.129");     /* Lokale IP-Adressen setzen */

    //connect to remote server
    if(connect(s,(struct sockaddr *)&server , sizeof(server)) < 0){
        puts(CONNECTION_ERROR);
        return 1;
    }
    puts(CONNECTED);

    //send data
    if(send(s, stringFileNames, 250, 0) < 0){
        puts("Send failed");
        return 1;
    }
    puts("Data send\n");

    //Receive reply from the server
    for (int i = 0; i < numberOfFiles; i++) {
        if ((recv_size = recv(s, serverReply, 256, 0)) == SOCKET_ERROR) {
            puts("recv failed");

            //Add a NULL terminating character to make it a proper string before printing
            exit(1);
        } else {
            serverReply[recv_size] = '\0';
            puts(serverReply);
        }
    }

    return 0;
}