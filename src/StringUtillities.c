//
// Created by Cedric on 06.12.2017.
//
#include <string.h>
#include "StringUtillities.h"

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
 * initialize a array with '\0'
 * @param array
 */
void initializeCharArray(char *array) {
    memset(&array, '\0', sizeof(array));
}
