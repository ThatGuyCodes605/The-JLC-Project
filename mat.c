#include <stdio.h>
#include <stdlib.h>
#define BUFFSIZE 1024
int main(int argc, char** argv) {
    char buff[BUFFSIZE];
    if (argc != 2) {
        fprintf(stderr, "Usage: mat <file>\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("FATAL ERROR");
        return 2;
    }
    while (fgets(buff, BUFFSIZE, fp) != NULL) {
        printf("%s", buff);
    }
    fclose(fp);
    return 0;
}