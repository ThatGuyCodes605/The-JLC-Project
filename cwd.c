#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    char *cwd = getcwd(NULL, 0);
    if (!cwd) { perror("FATAL ERROR"); return 1; }
    printf("%s\n", cwd);
    free(cwd);
    return 0;
}
