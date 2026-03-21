#include <stdio.h>
#include <string.h>
#define BUFFSIZE 1024
int main(int argc, char** argv) {
    if (argc > 2) {
        printf("Usage: hn\n");
        printf("Usage: hn <name>\n");
        return 1;
    }
    char buf[BUFFSIZE];
    FILE *f;
    if (argc < 2) {
        f = fopen("/etc/hostname", "r");
        if (f == NULL) {
            perror("FATAL ERROR");
            return 2;
        }
        while (fgets(buf, BUFFSIZE, f) != NULL) {
            printf("%s\n", buf);
        }
        fclose(f);
        return 0;
    }

    if (argc == 2) {
        f = fopen("/etc/hostname", "w");
        if (f == NULL) {
            perror("FATAL ERROR");
            return 2;
        }
        fprintf(f, "%s", argv[1]);
        fclose(f);
        return 0;
    }
    return -1; /* impossible error */
}