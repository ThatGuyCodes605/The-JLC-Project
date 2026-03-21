#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

static int is_dot(const char *s) {
    return (s[0] == '.' && s[1] == '\0') ||
           (s[0] == '.' && s[1] == '.' && s[2] == '\0');
}

static int del_r(const char *path) {
    struct stat st;
    if (lstat(path, &st) != 0) { perror(path); return 1; }
    if (!S_ISDIR(st.st_mode)) return unlink(path) != 0 ? (perror(path), 1) : 0;
    DIR *d = opendir(path);
    if (!d) { perror(path); return 1; }
    struct dirent *de;
    int err = 0;
    while ((de = readdir(d)) != NULL) {
        if (is_dot(de->d_name)) continue;
        char *sub = malloc(strlen(path) + strlen(de->d_name) + 2);
        if (!sub) { perror("malloc"); err = 1; continue; }
        sprintf(sub, "%s/%s", path, de->d_name);
        err |= del_r(sub);
        free(sub);
    }
    closedir(d);
    return rmdir(path) != 0 ? (perror(path), 1) : err;
}

int main(int argc, char **argv) {
    int recur = 0, start = 1;
    if (argc >= 2 && argv[1][0] == '-' && argv[1][1] == 'r' && argv[1][2] == '\0') {
        recur = 1; start = 2;
    }
    if (argc < 2 || (recur && argc < 3)) {
        fprintf(stderr, "Usage: del [-r] <file>...\n");
        return 1;
    }
    int err = 0;
    for (int i = start; i < argc; i++) {
        if (recur) err |= del_r(argv[i]);
        else if (unlink(argv[i]) != 0) { perror(argv[i]); err = 1; }
    }
    return err;
}

