#ifndef TLPI_HDR_H
#define TLPI_HDR_H /* Prevent accidental double inclusion*/

/* Expose POSIX prototypes (mkstemp, etc.). Must be defined before system
 * headers are included. Use 200809L for modern POSIX features.
 */
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "get_num.h"
#include "error_functions.h"

typedef enum
{
    TRUE = 1,
    FALSE = 0
} Boolean;

/* Use compiler extensions when available to avoid double evaluation */
#if defined(__GNUC__) || defined(__clang__)

#define MIN(a, b) \
    ({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); _a < _b ? _a : _b; })

#define MAX(a, b) \
    ({ __typeof__(a) _a = (a); __typeof__(b) _b = (b); _a > _b ? _a : _b; })

#else /* portable fallback (may evaluate args multiple times) */

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#endif /* compiler check */

#endif /* TLPI_HDR_H */