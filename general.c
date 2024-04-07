#include "general.h"

void myGets(char* buffer) {
    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';  // Replace the trailing newline character
        }
    } else {
        printf("Error reading input.\n");
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void readString(FILE* file, char** str) {
    char buffer[BUFFER_SIZE];
    if (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';  // Replace the trailing newline character
        }
        *str = (char*)malloc(len);
        CHECK_ALLOC_VOID(*str);
        strcpy(*str, buffer);
    } else {
        printf("Error reading from file.\n");
    }
}
