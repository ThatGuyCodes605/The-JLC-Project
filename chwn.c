/*
 * chwn - change file owner and group
 * Usage: chwn <owner:group> <file>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char** argv) {
    /* Check for correct number of arguments */
    if (argc != 3) {
        fprintf(stderr, "Usage: chwn <owner:group> <file>\n");
        return 1;
    }

    /* Find the colon separator in the owner:group argument */
    char *colon = argv[1];
    while (*colon && *colon != ':') colon++;

    /* Validate that we found a colon */
    if (!*colon) {
        fprintf(stderr, "Usage: chwn <owner:group> <file>\n");
        return 1;
    }

    /* Split the owner:group string */
    *colon = '\0';
    char *owner_str = argv[1];
    char *group_str = colon + 1;

    uid_t uid;
    gid_t gid;

    /* Get UID from username or numeric value */
    struct passwd *pw = getpwnam(owner_str);
    uid = pw ? pw->pw_uid : (uid_t)atoi(owner_str);

    /* Get GID from group name or numeric value */
    struct group *gr = getgrnam(group_str);
    gid = gr ? gr->gr_gid : (gid_t)atoi(group_str);

    /* Change ownership of the file */
    if (chown(argv[2], uid, gid) != 0) {
        perror("FATAL ERROR");
        return 2;
    }

    return 0;
}