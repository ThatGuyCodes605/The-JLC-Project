#include <stdio.h>
#include <sys/utsname.h>

// Ultra-minimal arch alternative with no external commands
int main(void) {
    struct utsname info;

    if (uname(&info) == 0) {
        puts(info.machine);
        return 0;
    } else {
        perror("uname");
        return 1;
    }
}