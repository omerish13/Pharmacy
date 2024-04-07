#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_ALLOC_VOID(ptr) if ((ptr) == NULL) { perror("Failed to allocate memory"); return; }
#define CHECK_ALLOC_INT(ptr) if ((ptr) == NULL) { perror("Failed to allocate memory"); return 0; }
#define CHECK_ALLOC_STRUCT(ptr) if ((ptr) == NULL) { perror("Failed to allocate memory"); return NULL; }
#define BUFFER_SIZE 1024  // Define a buffer size for input

/**
 * Reads a line of text from standard input and removes the newline character, if present.
 * Ensures the string is properly null-terminated.
 * 
 * @param buffer The character array where the input will be stored.
 * @param size The maximum number of characters to read, including the null terminator.
 */
void myGets(char* buffer);

/**
 * Clears the input buffer by reading and discarding any remaining characters up to the newline or EOF.
 */
void clearInputBuffer();

/**
 * Reads a string from a file and stores it in a dynamically allocated buffer.
 * 
 * @param file The file to read from.
 * @param str A pointer to a char pointer where the string will be stored.
 */
void readString(FILE* file, char** str);

#endif // GENERAL_H
