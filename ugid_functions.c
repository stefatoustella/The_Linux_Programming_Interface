#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ugid_functions.h"

char *
userNameFromId(uid_t uid)
{
    struct passwd *pwd;
    static char numstr[10];

    if ((pwd = getpwuid(uid)) == NULL)
    {
        snprintf(numstr, sizeof(numstr), "%ld", (long)uid);
        return numstr;
    }
    return pwd->pw_name;
}

uid_t userIdFromName(const char *name)
{
    struct passwd *pwd;
    uid_t u;
    char *endptr;

    if (name == NULL || *name == '\0')
        return -1;

    u = strtol(name, &endptr, 10);
    if (*endptr == '\0')
        return u;

    pwd = getpwnam(name);
    if (pwd == NULL)
        return -1;

    return pwd->pw_uid;
}

char *
groupNameFromId(gid_t gid)
{
    struct group *grp;
    static char numstr[10];

    if ((grp = getgrgid(gid)) == NULL)
    {
        snprintf(numstr, sizeof(numstr), "%ld", (long)gid);
        return numstr;
    }
    return grp->gr_name;
}

gid_t groupIdFromName(const char *name)
{
    struct group *grp;
    gid_t g;
    char *endptr;

    if (name == NULL || *name == '\0')
        return -1;

    g = strtol(name, &endptr, 10);
    if (*endptr == '\0')
        return g;

    grp = getgrnam(name);
    if (grp == NULL)
        return -1;

    return grp->gr_gid;
}