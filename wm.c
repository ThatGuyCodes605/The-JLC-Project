#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
int main() {
    uid_t user_id = getuid();
    struct passwd *user_info;
    user_info = getpwuid(user_id);
    printf("%s\n" , user_info->pw_name);
}