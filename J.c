#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: J dir\n");
        return 1;
    }
    if (chdir(argv[1]) != 0) {
        perror("J: cannot cd to");
        return 1;
    }
    return 0;
}
