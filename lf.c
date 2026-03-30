#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int cmp_str(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}
int main(int argc, char** argv) {
    struct dirent* de;
    DIR* dir;
    char** names = NULL;
    int count = 0;
   if (argc < 2) {
       dir = opendir (".");
   }
    else if (argc > 2) {
        fprintf(stderr, "Usage: lf [directory]\n");
        return 1;
    }
    else {
        dir = opendir(argv[1]);
    }
    if (dir == NULL) {
        perror ("FATAL ERROR");
        return 2;
    }
    while ((de = readdir(dir)) != NULL) {
        char **tmp = realloc(names, sizeof(char*) * (count + 1));
        if (tmp == NULL) { perror("FATAL ERROR"); closedir(dir); return 3; }
        names = tmp;
        names[count] = strdup(de->d_name);
        if (names[count] == NULL) { perror("FATAL ERROR"); closedir(dir); return 3; }
        count++;
    }
    closedir(dir);
    qsort(names, count, sizeof(char*), cmp_str);
   for (int i = 0; i < count; i++) {
        printf("%s\n", names[i]);
        free(names[i]);
    }
    free(names);
    return 0;
}
