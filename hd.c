#include <stdio.h>
#include <stdlib.h>
#define HD_BUFSIZ 4096

static void head(FILE *f, long n) {
    char buf[HD_BUFSIZ];
    for (long i = 0; i < n && fgets(buf, HD_BUFSIZ, f); i++)
        fputs(buf, stdout);
}

int main(int argc, char **argv) {
    long n = 10;
    int start = 1;
    if (argc >= 2 && argv[1][0] == '-' && argv[1][1] >= '1' && argv[1][1] <= '9') {
        n = atol(argv[1] + 1);
        start = 2;
    }
    if (start >= argc) {
        head(stdin, n);
        return 0;
    }
    int err = 0;
    for (int i = start; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (!f) { perror(argv[i]); err = 1; continue; }
        if (argc - start > 1) printf("==> %s <==\n", argv[i]);
        head(f, n);
        fclose(f);
    }
    return err;
}
