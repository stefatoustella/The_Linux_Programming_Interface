#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "get_num.h"
#include "error_functions.h"

/* Parse a string as a long with validation.
 *
 * Behavior improvements/changes vs. a naive implementation:
 * - Treats an input with no digits as a command-line error.
 * - Treats ERANGE from strtol specially (prints strtol error).
 * - Detects and rejects trailing non-digit junk.
 * - Honors the GN_ANY_BASE, GN_BASE_8 and GN_BASE_16 flags.
 */
long getLong(const char *arg, int flags, const char *name)
{
    char *endptr;
    long val;
    int base = 10;

    if (arg == NULL || *arg == '\0')
        cmdLineErr("NULL or empty string passed to %s", name);

    if (flags & GN_ANY_BASE)
        base = 0; /* let strtol() detect base from prefix */
    else if (flags & GN_BASE_8)
        base = 8;
    else if (flags & GN_BASE_16)
        base = 16;

    errno = 0;
    val = strtol(arg, &endptr, base);

    /* No digits were found */
    if (endptr == arg)
        cmdLineErr("No digits were found in %s", name);

    /* Range error */
    if (errno == ERANGE)
        errExit("strtol");

    /* Reject trailing junk (allowing trailing whitespace is optional;
       here we require the whole string to be a number). */
    /* skip any trailing whitespace */
    while (isspace((unsigned char)*endptr))
        endptr++;
    if (*endptr != '\0')
        cmdLineErr("junk characters after number: %s", arg);

    if ((flags & GN_NONNEG) && val < 0)
        cmdLineErr("%s must be >= 0", name);

    if ((flags & GN_GT_0) && val <= 0)
        cmdLineErr("%s must be > 0", name);

    return val;
}

int getInt(const char *arg, int flags, const char *name)
{
    long val = getLong(arg, flags, name);

    if (val > INT_MAX || val < INT_MIN)
        cmdLineErr("%s out of range for int", name);

    return (int)val;
}