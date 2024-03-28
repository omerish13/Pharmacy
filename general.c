#include "general.h"

void myGets(char* buffer, int size) {
    printf("Input: ");
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';  // Replace the trailing newline character
        }
    } else {
        printf("Error reading input.\n");
    }
}
