#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: brit <file>\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "w");
    if (f == NULL) {
        perror("FATAL ERROR");
        return 2;
    }
    int c;
    while ((c = fgetc(stdin)) != EOF) {
        fputc(c, stdout);
        fputc(c, f);
    }
    fclose(f);
    return 0;
}