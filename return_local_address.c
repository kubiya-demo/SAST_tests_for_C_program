#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FIXED: Return dynamically allocated memory instead of stack variable address
char* getLocalString() {
    // Allocate memory on heap, not stack
    char *heapString = (char*)malloc(14 * sizeof(char));
    
    if (heapString == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    
    // Copy string to heap-allocated memory
    strcpy(heapString, "Hello, World!");
    
    // Safe to return: memory persists after function returns
    return heapString;
}

int main() {
    char *str = getLocalString();
    
    if (str == NULL) {
        fprintf(stderr, "Error: Failed to get string\n");
        return 1;
    }
    
    // Now safe to use - memory is valid
    printf("String: %s\n", str);
    
    // IMPORTANT: Caller must free the allocated memory
    free(str);
    str = NULL;
    
    printf("\nNote: Stack address return prevented by:\n");
    printf("1. Allocating memory on heap (malloc) instead of stack\n");
    printf("2. Caller must free the returned memory\n");
    printf("3. Alternative: pass buffer as parameter for caller to provide\n");
    printf("4. Never return addresses of local variables\n");

    return 0;
}
