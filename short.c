#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Optimized version with better memory management and sorting algorithm
#define INITIAL_CAPACITY 1024
#define LINE_BUFFER_SIZE 2048

// Simple but efficient sorting algorithm for strings
static inline void insertion_sort(char **arr, int n) {
    for (int i = 1; i < n; i++) {
        char *key = arr[i];
        int j = i - 1;

        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: short <file>\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror(argv[1]);
        return 2;
    }

    // Dynamic array for better memory management
    char **lines = NULL;
    size_t capacity = INITIAL_CAPACITY;
    size_t count = 0;

    lines = malloc(capacity * sizeof(char*));
    if (!lines) {
        fclose(f);
        fprintf(stderr, "Memory allocation failed\n");
        return 3;
    }

    char buffer[LINE_BUFFER_SIZE];

    // Read all lines efficiently
    while (fgets(buffer, sizeof(buffer), f)) {
        // Resize array if needed
        if (count >= capacity) {
            capacity *= 2;
            char **temp = realloc(lines, capacity * sizeof(char*));
            if (!temp) {
                // Free all allocated memory
                for (size_t i = 0; i < count; i++) {
                    free(lines[i]);
                }
                free(lines);
                fclose(f);
                fprintf(stderr, "Memory allocation failed\n");
                return 3;
            }
            lines = temp;
        }

        // Allocate and copy line
        size_t len = strlen(buffer);
        lines[count] = malloc(len + 1);
        if (!lines[count]) {
            // Free all previously allocated memory
            for (size_t i = 0; i < count; i++) {
                free(lines[i]);
            }
            free(lines);
            fclose(f);
            fprintf(stderr, "Memory allocation failed\n");
            return 3;
        }
        memcpy(lines[count], buffer, len + 1);
        count++;
    }
    fclose(f);

    // Sort lines using efficient insertion sort
    insertion_sort(lines, count);

    // Output sorted lines
    for (size_t i = 0; i < count; i++) {
        fputs(lines[i], stdout);
        free(lines[i]);
    }
    free(lines);

    return 0;
}