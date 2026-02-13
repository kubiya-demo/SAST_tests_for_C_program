#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *source = "This string is too long for the buffer";
    // FIXED: Allocate sufficient memory based on actual string length
    size_t required_size = strlen(source) + 1;  // +1 for null terminator
    char *buffer = (char*)malloc(required_size * sizeof(char));

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Now safe to copy since we allocated enough space
    strncpy(buffer, source, required_size);
    buffer[required_size - 1] = '\0';  // Ensure null termination

    printf("Safely copied: %s\n", buffer);
    printf("Allocated %zu bytes for %zu character string\n", 
           required_size, strlen(source));

    free(buffer);
    return 0;
}
