/*
    FIXED: Demonstrates secure command execution with input validation.
    
    Previously: User input was concatenated directly into system() command,
    allowing arbitrary command injection (e.g., "; rm -rf /").
    
    Now: Uses input validation and safer alternatives to system().
    
    CWE-78: Improper Neutralization of Special Elements used in an OS Command
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Validate that input contains only safe characters (alphanumeric, space, dash, underscore)
int is_safe_input(const char *input) {
    for (size_t i = 0; i < strlen(input); i++) {
        if (!isalnum(input[i]) && input[i] != ' ' && 
            input[i] != '-' && input[i] != '_' && input[i] != '.') {
            return 0;  // Unsafe character found
        }
    }
    return 1;  // Input is safe
}

int main() {
    char userInput[256];

    printf("Enter text to echo (alphanumeric characters only): ");
    if (fgets(userInput, sizeof(userInput), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    // Remove newline character
    userInput[strcspn(userInput, "\n")] = '\0';

    // FIXED: Validate input before using it
    if (!is_safe_input(userInput)) {
        fprintf(stderr, "Error: Input contains unsafe characters. Only alphanumeric, "
                        "spaces, dashes, underscores, and periods are allowed.\n");
        return 1;
    }

    // SAFER ALTERNATIVE: Using printf instead of system for echo functionality
    // This completely avoids shell command execution
    printf("Echo (safe): %s\n", userInput);

    // If you absolutely must use system(), use strict validation and quoting
    // But the above printf approach is preferred for simple output
    
    printf("\nNote: Command injection vulnerability has been mitigated through:\n");
    printf("1. Input validation (whitelist approach)\n");
    printf("2. Using printf() instead of system() where possible\n");
    printf("3. Avoiding shell metacharacters (; | & $ ` \\ \" ' < > etc.)\n");

    return 0;
}
