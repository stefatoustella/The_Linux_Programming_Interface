#ifndef GET_NUM_H
#define GET_NUM_H

/* get_num.h
 * Small helper to parse numeric command-line arguments.
 * Provides getLong() and getInt() with simple validation flags.
 *
 * This header is C/C++ friendly.
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include <limits.h> /* for INT_MAX/INT_MIN used by getInt */
#include <stdlib.h> /* for long/int types */

/* Flags for parsing/validation */
#define GN_NONNEG 01 /* Value must be >= 0 */
#define GN_GT_0 02   /* Value must be > 0 */

#define GN_ANY_BASE 0100 /* Let strtol detect base (0x, leading 0, etc.) */
#define GN_BASE_8 0200   /* Force octal */
#define GN_BASE_16 0400  /* Force hexadecimal */

    /* Parse arg as a long.  On error the helper functions from
     * error_functions.h are used to print a message and exit.
     *
     * 'flags' is a bitmask formed from the GN_* constants above.
     * 'name' is used in error messages to identify the argument.
     */
    long getLong(const char *arg, int flags, const char *name);

    /* Like getLong but returns int and checks that the value fits in int. */
    int getInt(const char *arg, int flags, const char *name);

#ifdef __cplusplus
}
#endif

#endif /* GET_NUM_H */