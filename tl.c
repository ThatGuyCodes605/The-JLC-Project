#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TL_BUFSIZ 4096

static int tail(FILE *f, long n) {
    char **ring = malloc(n * sizeof(char*));
    if (!ring) { perror("malloc"); return 1; }
    for (long i = 0; i < n; i++) ring[i] = NULL;
    char buf[TL_BUFSIZ];
    long idx = 0;
    while (fgets(buf, TL_BUFSIZ, f)) {
        free(ring[idx % n]);
        ring[idx % n] = strdup(buf);
        idx++;
    }
    long show = (idx < n) ? idx : n;
    long base = (idx > n) ? (idx - n) : 0;
    for (long i = 0; i < show; i++) {
        char *line = ring[(base + i) % n];
        if (line) fputs(line, stdout);
    }
    for (long i = 0; i < n; i++) free(ring[i]);
    free(ring);
    return 0;
}

int main(int argc, char **argv) {
    long n = 10;
    int start = 1;
    if (argc >= 2 && argv[1][0] == '-' && argv[1][1] >= '1' && argv[1][1] <= '9') {
        n = atol(argv[1] + 1);
        start = 2;
    }
    if (start >= argc) return tail(stdin, n);
    int err = 0;
    for (int i = start; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (!f) { perror(argv[i]); err = 1; continue; }
        if (argc - start > 1) printf("==> %s <==\n", argv[i]);
        err |= tail(f, n);
        fclose(f);
    }
    return err;
}
