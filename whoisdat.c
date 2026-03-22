#include <stdio.h>
#include <pwd.h>
#include <unistd.h>

int main(void) {
    struct passwd *pw = getpwuid(getuid());
    if (!pw) {
        fprintf(stderr, "whoisdat: unknown user\n");
        return 1;
    }
    printf("%s\n", pw->pw_name);
    return 0;
}
