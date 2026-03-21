#include <stdio.h>
#include <string.h>

extern char **environ;

int main(int argc, char **argv) {
    for (char **e = environ; *e; e++) {
        if (argc < 2 || strncmp(*e, argv[1], strlen(argv[1])) == 0)
            puts(*e);
    }
    return 0;
}
