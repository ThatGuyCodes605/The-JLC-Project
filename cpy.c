#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

#define BUFFSIZE 1024
int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: cpy <source> <destination>\n");
        return 1;
    }
    FILE *source = fopen(argv[1], "rb");
    FILE *destination = fopen(argv[2], "wb");
    if (source == NULL) {
        perror("FATAL ERROR");
        return 2;
    }
    if (destination == NULL) {
        perror("FATAL ERROR");
        return 2;
    }

    /* Find the size of the source file. */
    struct stat st;
    if (fstat(fileno(source), &st) != 0) {
        perror("FATAL ERROR");
        fclose(source);
        fclose(destination);
        return 2;
    }

    size_t remaining = st.st_size;
    ssize_t sendfile_ret = 0;
    while ((sendfile_ret = sendfile(fileno(destination), fileno(source), NULL, remaining)) > 0) {
        /* Update the count of remaining bytes, removing those we've just transferred. */
        remaining -= sendfile_ret;
    }

    if (sendfile_ret < 0) { /* error happened */
        if (errno == EINVAL) { /* input file isn't mmap'able, fallback to fread/fwrite */
            char buff[BUFFSIZE];
            size_t nread;
            while ((nread = fread(buff, 1, BUFFSIZE, source)) > 0) {
                if (fwrite(buff, 1, nread, destination) != nread) {
                    perror("FATAL ERROR");
                    fclose(source);
                    fclose(destination);
                    return 3;
                }
            }
        } else {
            perror("FATAL ERROR");
            return 3;
        }
    }

    fclose(source);
    fclose(destination);
    return 0;
}
