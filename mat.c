#include <stdio.h>
#include <stdlib.h>
#define BUFFSIZE 1024
int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: mat <file>\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("FATAL ERROR");
        return 2;
    }
    char buff[BUFFSIZE];
    while (fgets(buff, BUFFSIZE, f) != NULL) {
        printf("%s", buff);
    }
    fclose(f);
    return 0;
}
