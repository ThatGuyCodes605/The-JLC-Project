#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_BUF 1024
void sort(int lines_filled, char **arr) {
    for (int i = 0; i < lines_filled - 1; i++) {
        for (int j = 0; j < lines_filled - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *tmp = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: srt <file>\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror(argv[1]); return 2;
    }
    char** buf = NULL;
    unsigned long lines_filled = 0;
    unsigned long size_of_buf = 4;
    buf = (char**)malloc(size_of_buf * sizeof(char*));
    char tmp[LINE_BUF];
    while (fgets(tmp, LINE_BUF, f) != NULL) {
        if (lines_filled == size_of_buf) {
            size_of_buf *= 2;
            buf = realloc(buf, size_of_buf * sizeof(char *));
            if (!buf) {
                perror("FATAL ERROR");
                fclose(f);
                return 3;
            }
        }
        buf[lines_filled++] = strdup(tmp);
    }
    fclose(f);
    sort(lines_filled, buf);
    for (size_t i = 0; i < lines_filled; i++) {
        printf("%s", buf[i]);
        free(buf[i]);
    }
    free(buf);
    return 0;
}