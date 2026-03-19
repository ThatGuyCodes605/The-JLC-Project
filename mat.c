#include <fcntl.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <unistd.h>
int main(int argc, char** argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: mat <file>\n");
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        perror("FATAL ERROR");
        return 2;
    }

    struct stat file_stat;
    if(stat(argv[1], &file_stat) == -1) {
        perror("FATAL ERROR");
        return 3;
    }

    if(sendfile(STDOUT_FILENO, fd, NULL, file_stat.st_size) == -1) {
        perror("FATAL ERROR");
        return 4;
    }
    close(fd);
    return 0;
}
