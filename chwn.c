#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: chwn <owner:group> <file>\n");
        return 1;
    }

    char *colon = argv[1];
    while (*colon && *colon != ':') colon++;

    if (!*colon) {
        fprintf(stderr, "Usage: chwn <owner:group> <file>\n");
        return 1;
    }

    *colon = '\0';
    char *owner_str = argv[1];
    char *group_str = colon + 1;

    uid_t uid;
    gid_t gid;

    struct passwd *pw = getpwnam(owner_str);
    uid = pw ? pw->pw_uid : (uid_t)atoi(owner_str);

    struct group *gr = getgrnam(group_str);
    gid = gr ? gr->gr_gid : (gid_t)atoi(group_str);

    if (chown(argv[2], uid, gid) != 0) {
        perror("FATAL ERROR");
        return 2;
    }

    return 0;
}