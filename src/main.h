//
// Created by Cedric on 06.12.2017.
//

#ifndef VSCLIENT_MAIN_H
#define VSCLIENT_MAIN_H

//--------------------constants------------------------------------------------//
static const int port = 32000;
static const char CREATE_SOCKET_ERROR[] = "Fehler beim erstellen des Socket";
static const char CONNECTION_ERROR[] = "Fehler beim Verbinden zum server";
static const char CONNECTED[] = "Erfolgreich zum Server verbunden";
//--------------------endConstants---------------------------------------------//

//--------------------prototypeFunctions-----------------------//
void getUserInput();
int connectToServer(const char *, int);
//--------------------endPrototypeFunctions--------------------//

#endif //VSCLIENT_MAIN_H
