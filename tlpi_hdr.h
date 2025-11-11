/* tlpi_hdr.h
 * Small header for The Linux Programming Interface examples
 * Defines MIN and MAX macros for two numeric values.
 *
 * For GCC/Clang we use typeof and a statement-expression so each argument
 * is evaluated exactly once. For other compilers we fall back to the
 * classic expression macros (which may evaluate arguments multiple times).
 */

#ifndef TLPI_HDR_H
#define TLPI_HDR_H /* Prevent accidental double inclusion*/

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
