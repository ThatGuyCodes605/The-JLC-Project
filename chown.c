#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: chown <owner:group> <file>\n");
        return 1;
    }

    // Parse owner:group format
    char *colon = argv[1];
    while (*colon && *colon != ':') colon++;

    if (!*colon) {
        printf("Usage: chown <owner:group> <file>\n");
        return 1;
    }

    *colon = '\0';
    char *owner_str = argv[1];
    char *group_str = colon + 1;

    int owner = atoi(owner_str);
    int group = atoi(group_str);

    if (chown(argv[2], owner, group) != 0) {
        perror("FATAL ERROR");
        return 2;
    }

    return 0;
}