#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

static int mkd_p(const char *path) {
    char *tmp = strdup(path);
    if (!tmp) { perror("strdup"); return 1; }
    for (char *p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(tmp, 0755) != 0 && errno != EEXIST) { /* 0755 = rwxr-xr-x */
                perror(tmp); free(tmp); return 1;
            }
            *p = '/';
        }
    }
    if (mkdir(tmp, 0755) != 0 && errno != EEXIST) { /* 0755 = rwxr-xr-x */
        perror(tmp); free(tmp); return 1;
    }
    free(tmp);
    return 0;
}

int main(int argc, char **argv) {
    int parents = 0, start = 1;
    if (argc >= 2 && strcmp(argv[1], "-p") == 0) { parents = 1; start = 2; }
    if (argc < 2 || (parents && argc < 3)) {
        fprintf(stderr, "Usage: mkd [-p] <dir>...\n");
        return 1;
    }
    int err = 0;
    for (int i = start; i < argc; i++) {
        if (parents) { if (mkd_p(argv[i])) err = 1; }
        else if (mkdir(argv[i], 0755) != 0) { perror(argv[i]); err = 1; } /* 0755 = rwxr-xr-x */
    }
    return err;
}
