#include <stdio.h>
int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: move <file> <destination>\n");
        return 1;
    }
    if (rename(argv[1], argv[2]) != 0) {
        perror("FATAL ERROR");
        return 2;
    }
    return 0;
}