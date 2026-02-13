/*
    FIXED: Properly free all allocated memory including nested structures.
    
    Previously: The program freed the outer structs but forgot to free
    the inner arrays, causing memory leaks.
    
    Now: All dynamically allocated memory is properly freed in reverse order.
    
    CWE-401: Missing Release of Memory after Effective Lifetime
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* innerArray;
    int size;
} MyStruct;

int main() {
    int numStructs = 5; // Number of structs in the meta-array
    MyStruct **outerArray = (MyStruct**)malloc(numStructs * sizeof(MyStruct*));

    if (outerArray == NULL) {
        perror("Failed to allocate memory for outerArray");
        return 1;
    }

    // Allocate and initialize each struct and its inner array
    for (int i = 0; i < numStructs; ++i) {
        outerArray[i] = (MyStruct*)malloc(sizeof(MyStruct));
        if (outerArray[i] == NULL) {
            perror("Failed to allocate memory for outerArray element");
            // Free already allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(outerArray[j]->innerArray);
                free(outerArray[j]);
            }
            free(outerArray);
            return 1;
        }
        
        outerArray[i]->size = 10; // Size of the inner array
        outerArray[i]->innerArray = (int*)malloc(outerArray[i]->size * sizeof(int));
        if (outerArray[i]->innerArray == NULL) {
            perror("Failed to allocate memory for innerArray");
            // Free already allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(outerArray[j]->innerArray);
                free(outerArray[j]);
            }
            free(outerArray[i]);  // Free the current struct too
            free(outerArray);
            return 1;
        }

        // Initialize the inner array with values
        for (int j = 0; j < outerArray[i]->size; j++) {
            outerArray[i]->innerArray[j] = j;
        }
    }

    // ... Use outerArray and its inner arrays ...
    printf("All memory allocated and initialized successfully\n");

    // FIXED: Free all memory in reverse order of allocation
    for (int i = 0; i < numStructs; ++i) {
        // First free the inner array
        free(outerArray[i]->innerArray);
        // Then free the struct itself
        free(outerArray[i]);
    }
    // Finally free the outer array
    free(outerArray);

    printf("All memory properly freed - no memory leaks\n");

    return 0;
}
