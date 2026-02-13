/*
    FIXED: Demonstrates secure credential handling using environment variables.
    
    Previously: Password was hardcoded in source code ("secret123").
    Now: Reads password from environment variable with proper error handling.
    
    CWE-798: Use of Hard-coded Credentials
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char inputPassword[50];
    
    // FIXED: Read password from environment variable instead of hardcoding
    const char *systemPassword = getenv("SYSTEM_PASSWORD");
    
    if (systemPassword == NULL) {
        fprintf(stderr, "Error: SYSTEM_PASSWORD environment variable not set.\n");
        fprintf(stderr, "Please set it using: export SYSTEM_PASSWORD=your_secure_password\n");
        return 1;
    }

    printf("Enter password to access the system file: ");
    if (fgets(inputPassword, sizeof(inputPassword), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    inputPassword[strcspn(inputPassword, "\n")] = '\0'; // Remove newline character

    if (strcmp(inputPassword, systemPassword) == 0) {
        printf("Access granted. Reading system file...\n");

        // Attempting to read a system-critical file (with a fake filename)
        const char *criticalFilePath = "/etc/fake_critical_file.conf";
        FILE *file = fopen(criticalFilePath, "r");

        if (file == NULL) {
            perror("Error opening file");
        } else {
            // Read and print the contents of the file (hypothetical)
            char buffer[256];
            while (fgets(buffer, sizeof(buffer), file) != NULL) {
                printf("%s", buffer);
            }
            fclose(file);
        }
    } else {
        printf("Access denied.\n");
    }

    printf("\nNote: Hard-coded credentials vulnerability mitigated by:\n");
    printf("1. Reading password from environment variable\n");
    printf("2. Never storing credentials in source code\n");
    printf("3. In production, use proper secret management (vault, key management service)\n");

    return 0;
}
