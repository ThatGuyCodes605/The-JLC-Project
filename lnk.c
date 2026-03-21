#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int sym = 0, start = 1;
    if (argc >= 2 && strcmp(argv[1], "-s") == 0) { sym = 1; start = 2; }
    if (argc < start + 2) {
        fprintf(stderr, "Usage: lnk [-s] <target> <link>\n");
        return 1;
    }
    int r = sym ? symlink(argv[start], argv[start + 1])
                : link(argv[start], argv[start + 1]);
    if (r != 0) { perror("FATAL ERROR"); return 2; }
    return 0;
}
