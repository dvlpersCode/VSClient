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
    int port = 0;
    char ip;

    while (exit == 0) {
        //initialize the char array
        initializeCharArray(fileNamesString);

        //read number of bytes that the user wants to receive from the server and copy the result to byteNumbersAsChar
        strcpy(byteNumberAsChar, readNumberOfBytes());

        //append the char array to the fileNamesString
        appendToFileString(fileNamesString, byteNumberAsChar);

        numberOfFiles = readFiles(fileNamesString);

        port = readPort();

        ip = readIP();

        connectToServer(fileNamesString, numberOfFiles, port, ip);

        exit = 1;
    }
}

int connectToServer(const char* stringFileNames, int numberOfFiles, int port, char* ip){
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
    server.sin_addr.s_addr = inet_addr(ip);   /* Lokale IP-Adressen setzen */

    //connect to remote server
    if(connect(s,(struct sockaddr *)&server , sizeof(server)) < 0){
        puts(CONNECTION_ERROR);
        return 1;
    }
    puts(CONNECTED);

    //send data
    if(send(s, stringFileNames, sizeof(*stringFileNames), 0) < 0){
        puts("Send failed");
        return 1;
    }
    puts("Data send\n");

    //receiving a reply from the server
    for (int i = 0; i < numberOfFiles; i++) {
        initializeCharArray(serverReply);
        if ((recv_size =recv(s, serverReply, 256, MSG_PEEK)) == SOCKET_ERROR) {
            puts("Error while receiving a reply from the server.");
        } else {
            serverReply[recv_size] = '\0';
            printf("Data received : %s", serverReply);
        }
    }
    closesocket(s);
    WSACleanup();

    return 0;
}