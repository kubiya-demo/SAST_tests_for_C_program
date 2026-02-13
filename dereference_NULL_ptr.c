#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = NULL;
    
    // FIXED: Always check for NULL before dereferencing pointers
    if (ptr == NULL) {
        fprintf(stderr, "Error: Pointer is NULL, cannot dereference\n");
        fprintf(stderr, "Allocating memory and initializing...\n");
        
        // Properly allocate memory
        ptr = (int*)malloc(sizeof(int));
        if (ptr == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        
        // Initialize the value
        *ptr = 42;
    }
    
    // Now safe to dereference
    printf("Value: %d\n", *ptr);
    
    // Clean up
    free(ptr);
    ptr = NULL;  // Good practice: set to NULL after free
    
    printf("\nNote: NULL pointer dereference prevented by:\n");
    printf("1. Always check pointers for NULL before dereferencing\n");
    printf("2. Initialize pointers properly or allocate memory\n");
    printf("3. Check return values from functions that return pointers\n");

    return 0;
}
