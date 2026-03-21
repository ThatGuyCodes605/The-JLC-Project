#include <stdio.h>

static void count(FILE *f, long *l, long *w, long *b) {
    int c, in_word = 0;
    *l = *w = *b = 0;
    while ((c = fgetc(f)) != EOF) {
        (*b)++;
        if (c == '\n') (*l)++;
        if (c == ' ' || c == '\t' || c == '\n') in_word = 0;
        else if (!in_word) { in_word = 1; (*w)++; }
    }
}

int main(int argc, char **argv) {
    long l, w, b, tl = 0, tw = 0, tb = 0;
    int err = 0;
    if (argc < 2) {
        count(stdin, &l, &w, &b);
        printf("%7ld %7ld %7ld\n", l, w, b);
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if (!f) { perror(argv[i]); err = 1; continue; }
        count(f, &l, &w, &b);
        fclose(f);
        printf("%7ld %7ld %7ld %s\n", l, w, b, argv[i]);
        tl += l; tw += w; tb += b;
    }
    if (argc > 2) printf("%7ld %7ld %7ld total\n", tl, tw, tb);
    return err;
}
