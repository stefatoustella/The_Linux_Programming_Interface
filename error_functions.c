/*
 * error_functions.c
 * Implementations of the error-reporting helpers declared in
 * error_functions.h. This version is defensive:
 * - It does NOT include tlpi_hdr.h (avoids circular includes).
 * - It includes ename.c.inc only if present (using __has_include when available).
 * - It works even if the optional ename table is not available.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "error_functions.h"

/* If ename.c.inc is present it provides an `ename[]` table and MAX_ENAME.
 * Include it only when present so build succeeds whether or not you have
 * TLPI's ename table file.
 */
#if defined(__has_include)
#if __has_include("ename.c.inc")
#include "ename.c.inc"
#endif
#else
/* Older compilers: try unguarded include (will fail at compile time if not present)
 * If you don't have ename.c.inc, the implementation below still works
 * because we check for MAX_ENAME before using ename[].
 */
#include "ename.c.inc"
#endif

/* terminate: if EF_DUMPCORE is set, abort to produce a core dump; otherwise
 * either call exit() (if useExit3 != 0) or _exit() to avoid flushing stdio
 * buffers a second time.
 */
#ifdef __GNUC__
__attribute__((__noreturn__))
#endif
static void
terminate(int useExit3)
{
    char *s = getenv("EF_DUMPCORE");

    if (s != NULL && *s != '\0')
        abort();

    if (useExit3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}

/* outputError: format an error message and write it to stderr. If useErr
 * is nonzero, include the text for the errno value 'err'. If flushStdout is
 * nonzero, fflush(stdout) before writing the message.
 */
static void
outputError(int useErr, int err, int flushStdout,
            const char *format, va_list ap)
{
#define BUF_SIZE 500
    char userMsg[BUF_SIZE];
    char errText[BUF_SIZE];

    vsnprintf(userMsg, BUF_SIZE, format, ap);

    if (useErr)
    {
        const char *ename_str = NULL;
#ifdef MAX_ENAME
        if (err >= 0 && err <= MAX_ENAME)
            ename_str = ename[err];
#endif
        if (ename_str != NULL)
            snprintf(errText, BUF_SIZE, " [%s %s]", ename_str, strerror(err));
        else
            snprintf(errText, BUF_SIZE, " [%s]", strerror(err));
    }
    else
        snprintf(errText, BUF_SIZE, ":");

    /* Write the pieces directly to stderr to avoid building a large
     * intermediate string (and to silence snprintf truncation warnings).
     */
    if (flushStdout)
        fflush(stdout);

    fputs("ERROR", stderr);
    fputs(errText, stderr);
    fputc(' ', stderr);
    fputs(userMsg, stderr);
    fputc('\n', stderr);
    fflush(stderr);
#undef BUF_SIZE
}

void errMsg(const char *format, ...)
{
    va_list argList;
    int savedErrno = errno; /* In case we change it here */

    va_start(argList, format);
    outputError(1, savedErrno, 1, format, argList);
    va_end(argList);

    errno = savedErrno;
}

void errExit(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(1, errno, 1, format, argList);
    va_end(argList);

    terminate(1);
}

void err_exit(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(1, errno, 0, format, argList);
    va_end(argList);

    terminate(1);
}

void errExitEN(int errnum, const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(1, errnum, 1, format, argList);
    va_end(argList);

    terminate(1);
}

void fatal(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(0, 0, 1, format, argList);
    va_end(argList);

    terminate(1);
}

void usageErr(const char *format, ...)
{
    va_list argList;

    fflush(stdout); /* Flush any pending stdout */
    fprintf(stderr, "Usage: ");

    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format, ...)
{
    va_list argList;

    fflush(stdout); /* Flush any pending stdout */
    fprintf(stderr, "Command-line usage error: ");

    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr); /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}