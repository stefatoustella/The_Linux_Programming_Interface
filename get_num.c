#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_num.h"
#include "error_functions.h"

long getLong(const char *arg, int flags, const char *name)
{
    char *endptr;
    long val;
    int base = 10;

    if (arg == NULL || *arg == '\0')
        cmdLineErr("NULL or empty string passed to %s\n", name);

    if (flags & GN_ANY_BASE)
        base = 0; /* let strtol() detect base */
    else if (flags & GN_BASE_8)
        base = 8;
    else if (flags & GN_BASE_16)
        base = 16;

    errno = 0;
    val = strtol(arg, &endptr, base);
    if (errno != 0)
        errExit("strtol");

    if (*endptr != '\0')
        cmdLineErr("junk characters after number: %s\n", arg);

    if ((flags & GN_NONNEG) && val < 0)
        cmdLineErr("%s must be >= 0\n", name);

    if ((flags & GN_GT_0) && val <= 0)
        cmdLineErr("%s must be > 0\n", name);

    return val;
}

int getInt(const char *arg, int flags, const char *name)
{
    long val = getLong(arg, flags, name);
    if (val > INT_MAX || val < INT_MIN)
        cmdLineErr("%s out of range for int\n", name);
    return (int)val;
}
