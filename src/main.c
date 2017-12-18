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
    char ip[15];

    while (exit == 0) {
        //initialize the char array
        initializeCharArray(fileNamesString, 250);

        //read number of bytes that the user wants to receive from the server and copy the result to byteNumbersAsChar
        strcpy(byteNumberAsChar, readNumberOfBytes());

        //append the char array to the fileNamesString
        appendToFileString(fileNamesString, byteNumberAsChar);

        numberOfFiles = readFiles(fileNamesString);

        port = readPort();

        readIP(ip);

        connectToServer(fileNamesString, numberOfFiles, port, ip);

        exit = 1;
    }
}

int connectToServer(const char* stringFileNames, int numberOfFiles, int port, char* ip){
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char serverReply[RECEIVE_SIZE];
    int recv_size;

    printf(WINSOCK_INITIALISING);
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0){
        printf("%s %d", CREATE_SOCKET_ERROR, WSAGetLastError());
        return 1;
    }
    printf(INITIALIZED);

    //create Socket
    if((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
        printf(CREATING_SOCKET_ERROR, WSAGetLastError());
    }
    printf(SOCKET_CREATED);

    server.sin_family = AF_INET;             /* Familie auf Internet setzen */
    server.sin_port = htons((u_short) port);  /* host-byte-order -> network byte-order */
    server.sin_addr.s_addr = inet_addr(ip);   /* Lokale IP-Adressen setzen */

    //connect to remote server
    if(connect(s,(struct sockaddr *)&server , sizeof(server)) < 0){
        puts(CONNECTION_ERROR);
        return 1;
    }
    puts(CONNECTED);

    //send data
    if(send(s, stringFileNames, 256, 0) < 0){
        puts(SENDING_DATA_ERROR);
        return 1;
    }
    puts(DATA_SEND);

    //receiving a reply from the server
    memset(&serverReply, '\0', RECEIVE_SIZE);
    recv_size = recv(s, serverReply, RECEIVE_SIZE, MSG_PEEK);
    if (recv_size < 0) {
        puts(ERROR_RECEIVIING_DATA);
        printf("%s %d", ERROR_RECEIVIING_DATA, WSAGetLastError());
    } else {
        printf(DATA_RECEIVED, serverReply);
        initializeCharArray(serverReply, RECEIVE_SIZE);
    }
    closesocket(s);
    WSACleanup();

    return 0;
}