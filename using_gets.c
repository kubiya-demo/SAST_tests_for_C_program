#include <stdio.h>
#include <string.h>

int main() {
    char buffer[50];

    printf("Enter a string: ");
    // FIXED: Replaced unsafe gets() with fgets() which performs bounds checking
    // gets() was removed from C11 due to CVE-2006-7140
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Remove trailing newline if present
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("You entered: %s\n", buffer);
    } else {
        printf("Error reading input\n");
        return 1;
    }

    return 0;
}
