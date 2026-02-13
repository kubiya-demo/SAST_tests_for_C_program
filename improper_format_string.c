#include <stdio.h>
#include <string.h>

int main() {
    char buf[100];
    
    printf("Enter text: ");
    // FIXED: Added format specifier and size limit to scanf
    if (scanf("%99s", buf) != 1) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    // FIXED: Never use user input directly as format string
    // Original vulnerability: printf(buf) allows format string attacks
    // An attacker could input "%x %x %x %x" to read stack memory
    // or "%n" to write to arbitrary memory locations
    
    printf("You entered: %s\n", buf);  // Safe: buf is treated as data, not format
    
    printf("\nNote: Format string vulnerability mitigated by:\n");
    printf("1. Using %%s format specifier so input is treated as data\n");
    printf("2. Never passing user input directly to printf/sprintf/fprintf\n");
    printf("3. Always use printf(\"%%s\", user_input) instead of printf(user_input)\n");
    
    return 0;
}
