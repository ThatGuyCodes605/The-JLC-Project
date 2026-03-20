#include <stdio.h>
#include <stdlib.h>
#define BUFFSIZE 1024
int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: cpy <source> <destination>\n");
        return 1;
    }
    FILE *source = fopen(argv[1], "r");
    FILE *destination = fopen(argv[2], "w");
    if (source == NULL) {
        perror("FATAL ERROR");
        return 2;
    }
    if (destination == NULL) {
        perror("FATAL ERROR");
        return 2;
    }
    char buff[BUFFSIZE];
    while (fgets(buff, BUFFSIZE, source) != NULL) {
        fputs(buff, destination);
    }
    fclose(source);
    fclose(destination);
    return 0;
}