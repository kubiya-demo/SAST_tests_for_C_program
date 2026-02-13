/*
    FIXED: Ensure memory is freed in all code paths.
    
    Previously: The program leaked memory when file opening failed (return -1 path).
    Now: All error paths properly clean up allocated resources.
    
    CWE-401: Missing Release of Memory after Effective Lifetime
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Allocate memory
    char *buffer = (char*)malloc(sizeof(char));
    if (buffer == NULL) {
        return 2; // Return 2 in case memory allocation fails
    }

    // Open a common file
    FILE *file = fopen("/etc/passwd", "r");
    if (file == NULL) {
        // FIXED: Free buffer before returning on error
        free(buffer);
        return -1; // Return -1 if file opening fails (no longer leaks memory)
    }

    // Read the first character
    char firstChar = fgetc(file);
    if (firstChar != EOF) {
        *buffer = firstChar;
        printf("First character in file: %c\n", *buffer);
    }

    // Close file and free memory
    fclose(file);
    free(buffer);

    printf("All resources properly cleaned up\n");

    return 0;
}
