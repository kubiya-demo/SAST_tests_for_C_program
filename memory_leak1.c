#include <stdlib.h>
#include <stdio.h>

void func() {
    char *ptr = malloc(10); // Memory allocated
    
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    
    // Use the memory...
    ptr[0] = 'A';
    
    // FIXED: Free allocated memory before function returns
    free(ptr);
    printf("Memory properly freed in func()\n");
}

int main() {
    func();
    printf("No memory leak - all allocated memory has been freed\n");
    return 0;
}
