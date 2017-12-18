//
// Created by Cedric on 06.12.2017.
//

#ifndef VSCLIENT_MAIN_H
#define VSCLIENT_MAIN_H

//--------------------constants------------------------------------------------//
static const int RECEIVE_SIZE = 320;
static const char CREATE_SOCKET_ERROR[] = "Fehler beim erstellen des Socket";
static const char CONNECTION_ERROR[] = "Fehler beim Verbinden zum server";
static const char CONNECTED[] = "Erfolgreich zum Server verbunden";
static const char WINSOCK_INITIALISING[] = "\n Initialising Winsock...";
static const char INITIALIZED[] = "\n Initialised \n";
static const char CREATING_SOCKET_ERROR[] = "Could not create Socket : %d";
static const char SOCKET_CREATED[] = "Socket created. \n";
static const char SENDING_DATA_ERROR[] = "Send failed";
static const char DATA_SEND[] = "Data send\n";
static const char ERROR_RECEIVIING_DATA[] = "Error while receiving a reply from the server.";
static const char DATA_RECEIVED[] = "Data received :\n%s\n";
//--------------------endConstants---------------------------------------------//

//--------------------prototypeFunctions-----------------------//
void getUserInput();
int connectToServer(const char *, int, int , char *);
//--------------------endPrototypeFunctions--------------------//

#endif //VSCLIENT_MAIN_H
