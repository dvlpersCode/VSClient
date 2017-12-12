//
// Created by Cedric on 06.12.2017.
//

#ifndef VSCLIENT_CLIENTINPUT_H
#define VSCLIENT_CLIENTINPUT_H

//-----------------------------------------constant------------------------------------------------------------//
static const char READ_BYTE_NUMBER[] = "Wie viele Bytes wollen Sie von dem Server erhalten (n <= 10): \n n = ";
static const char READ_NUMBER_OF_FILES[] = "Wie viele Dateinamen wollen Sie an den Server senden? \n Anzahl: ";
static const char READ_FILE_NAME[] = "Lese Dateiname: ";
static const char READ_PORT[] = "Lese Port: ";
static const char READ_IP[] = "Lese IP-Adresse: ";
//-----------------------------------------endConstant---------------------------------------------------------//

//--------------------prototypeFunctions-----------------------//
char *readNumberOfBytes();
int readFiles(char *);
void readFileNames(char *);
int readNumberFromTerminal();
int readPort();
void readIP(char *);
//--------------------endPrototypeFunctions--------------------//

#endif //VSCLIENT_CLIENTINPUT_H
