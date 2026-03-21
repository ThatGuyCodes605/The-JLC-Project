#include <stdio.h>
#include <utime.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: tch <file>...\n");
        return 1;
    }
    int err = 0;
    for (int i = 1; i < argc; i++) {
        struct stat st;
        if (stat(argv[i], &st) != 0) {
            FILE *f = fopen(argv[i], "a");
            if (!f) { perror(argv[i]); err = 1; continue; }
            fclose(f);
        } else {
            if (utime(argv[i], NULL) != 0) { perror(argv[i]); err = 1; }
        }
    }
    return err;
}
