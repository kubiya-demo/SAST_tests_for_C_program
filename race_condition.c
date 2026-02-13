#include <pthread.h>
#include <stdio.h>

volatile int counter = 0;  // Global counter
// FIXED: Add mutex for thread synchronization
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void* incrementCounter(void* arg) {
    for (int i = 0; i < 100000; ++i) {
        // FIXED: Protect critical section with mutex
        pthread_mutex_lock(&counter_mutex);
        counter++;  // Now safe from race conditions
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    printf("Starting race condition test with mutex protection...\n");

    // Create two threads that increment the counter
    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the final value of counter
    printf("Final counter value: %d\n", counter);
    printf("Expected value: %d\n", 200000);
    
    if (counter == 200000) {
        printf("Success: Race condition prevented by mutex!\n");
    } else {
        printf("Warning: Counter mismatch (should not happen with proper locking)\n");
    }

    // Clean up mutex
    pthread_mutex_destroy(&counter_mutex);

    printf("\nNote: Race condition prevented by:\n");
    printf("1. Using pthread_mutex to protect critical sections\n");
    printf("2. Lock before accessing shared data, unlock after\n");
    printf("3. Alternative: use atomic operations (C11 _Atomic)\n");

    return 0;
}
