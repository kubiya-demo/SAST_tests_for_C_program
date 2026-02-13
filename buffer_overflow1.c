#include <stdio.h>
#include <string.h>

int main() {
    char buffer[10];
    const char *source = "This string is way too long for the buffer";
    
    // FIXED: Replaced unsafe strcpy() with strncpy() with size limit
    // strcpy() does not check buffer bounds and causes buffer overflow
    strncpy(buffer, source, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';  // Ensure null termination
    
    printf("Safely copied (truncated): %s\n", buffer);
    printf("Original string length: %zu, Buffer size: %zu\n", 
           strlen(source), sizeof(buffer));
    
    return 0;
}
