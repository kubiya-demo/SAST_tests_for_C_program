#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// FIXED: Helper function to safely add integers with overflow detection
bool safe_add(int a, int b, int *result) {
    // Check for overflow before performing addition
    if (a > 0 && b > INT_MAX - a) {
        return false;  // Overflow would occur
    }
    if (a < 0 && b < INT_MIN - a) {
        return false;  // Underflow would occur
    }
    
    *result = a + b;
    return true;  // Addition is safe
}

int main() {
    int max_int = INT_MAX;
    int result;

    printf("Max int: %d\n", max_int);
    
    // FIXED: Check for overflow before performing arithmetic
    if (safe_add(max_int, 1, &result)) {
        printf("Max int + 1: %d\n", result);
    } else {
        printf("Error: Integer overflow detected!\n");
        printf("Cannot add 1 to INT_MAX (%d) without overflow\n", max_int);
    }

    // Demonstrate safe addition with normal values
    int a = 100, b = 200;
    if (safe_add(a, b, &result)) {
        printf("\nSafe addition: %d + %d = %d\n", a, b, result);
    }

    printf("\nNote: Integer overflow prevented by:\n");
    printf("1. Checking for overflow before arithmetic operations\n");
    printf("2. Using overflow detection functions\n");
    printf("3. Consider using compiler builtins: __builtin_add_overflow()\n");

    return 0;
}
