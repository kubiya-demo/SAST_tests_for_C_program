#include <stdio.h>

#define ARRAY_SIZE 5

int main() {
    int array[ARRAY_SIZE] = {1, 2, 3, 4, 5};

    // Correctly accessing the array
    printf("Array elements: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // FIXED: Added bounds checking before array access
    int index = 5;  // This would be out of bounds
    
    if (index >= 0 && index < ARRAY_SIZE) {
        printf("array[%d] = %d\n", index, array[index]);
    } else {
        printf("Error: Index %d is out of bounds (array size: %d)\n", 
               index, ARRAY_SIZE);
        printf("Valid indices are 0 to %d\n", ARRAY_SIZE - 1);
    }

    printf("\nNote: Out-of-bounds access prevented by:\n");
    printf("1. Always validating array indices before access\n");
    printf("2. Using array size constant (ARRAY_SIZE) instead of magic numbers\n");
    printf("3. Checking: 0 <= index < array_size\n");

    return 0;
}
