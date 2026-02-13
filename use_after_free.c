#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer = (char*)malloc(100 * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Use the buffer for some operation
    snprintf(buffer, 100, "Sample text for buffer.");
    printf("Buffer content before free: %s\n", buffer);

    // Free the buffer
    free(buffer);
    
    // FIXED: Set pointer to NULL after free to prevent use-after-free
    // This makes any accidental dereference cause an immediate segfault
    // rather than unpredictable behavior or security vulnerabilities
    buffer = NULL;

    // Now if we try to use buffer, it will be NULL and we can check for it
    if (buffer != NULL) {
        printf("Buffer content after free: %s\n", buffer);
    } else {
        printf("Buffer safely set to NULL after free - preventing use-after-free\n");
    }

    // Best practice: Don't access freed memory at all
    printf("\nNote: Use-after-free vulnerability mitigated by:\n");
    printf("1. Setting pointer to NULL immediately after free()\n");
    printf("2. Checking for NULL before any pointer dereference\n");
    printf("3. Never accessing memory after it has been freed\n");

    return 0;
}
