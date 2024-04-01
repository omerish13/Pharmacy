#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_ALLOC(ptr) if ((ptr) == NULL) { perror("Failed to allocate memory"); exit(EXIT_FAILURE); }
#define BUFFER_SIZE 1024  // Define a buffer size for input

/**
 * Reads a line of text from standard input and removes the newline character, if present.
 * Ensures the string is properly null-terminated.
 * 
 * @param buffer The character array where the input will be stored.
 * @param size The maximum number of characters to read, including the null terminator.
 */
void myGets(char* buffer);

#endif // GENERAL_H
