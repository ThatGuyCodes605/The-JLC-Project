#include <stdio.h>
#include <string.h>
#define BUFFSIZE 1024
int main(int argc, char** argv) {
    char buff[BUFFSIZE];
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: jgrep <pattern> <file>\n");
        return 1;
    }
    FILE* file;
    if (argc == 3) {
        file = fopen(argv[2], "r");
        if (file == NULL) {
            perror("FATAL ERROR");
            return 2;
        }
    } else {
        file = stdin;
    }

    while (fgets(buff, BUFFSIZE, file) != NULL) {
        if (strstr(buff, argv[1]) != NULL) {
            printf("%s", buff);
        }
        else {
            printf("NOT FOUND\n");
            return 3;
        }
    }
    if (argc == 3) {
        fclose(file);
    }
    return 0;
}