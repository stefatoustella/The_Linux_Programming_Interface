/*
 * Minimal support to satisfy TLPI-style error helper calls
 * (errExit, cmdLineErr, usageErr, errMsg). This is purposely small:
 * prints a message and exits (or returns for nonfatal errMsg).
 *
 * Use this only if you don't want or don't have the full TLPI
 * error_functions.c implementation.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Nonfatal message — does not exit */
void errMsg(const char *format, ...)
{
    va_list ap;
    int savedErrno = errno;

    va_start(ap, format);
    if (format && *format)
        vfprintf(stderr, format, ap);
    va_end(ap);

    if (savedErrno)
        fprintf(stderr, ": %s", strerror(savedErrno));

    fputc('\n', stderr);
    errno = savedErrno;
}

/* Terminate with message and errno text */
__attribute__((noreturn)) void errExit(const char *format, ...)
{
    va_list ap;
    int savedErrno = errno;

    va_start(ap, format);
    if (format && *format)
        vfprintf(stderr, format, ap);
    va_end(ap);

    if (savedErrno)
        fprintf(stderr, ": %s\n", strerror(savedErrno));
    else
        fputc('\n', stderr);

    exit(EXIT_FAILURE);
}

/* legacy alias */
__attribute__((noreturn)) void err_exit(const char *format, ...)
{
    va_list ap;
    int savedErrno = errno;

    va_start(ap, format);
    if (format && *format)
        vfprintf(stderr, format, ap);
    va_end(ap);

    if (savedErrno)
        fprintf(stderr, ": %s\n", strerror(savedErrno));
    else
        fputc('\n', stderr);

    exit(EXIT_FAILURE);
}

/* Terminate reporting an explicit errno */
__attribute__((noreturn)) void errExitEN(int errnum, const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    if (format && *format)
        vfprintf(stderr, format, ap);
    va_end(ap);

    if (errnum)
        fprintf(stderr, ": %s\n", strerror(errnum));
    else
        fputc('\n', stderr);

    exit(EXIT_FAILURE);
}

/* Fatal (no errno) */
__attribute__((noreturn)) void fatal(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    if (format && *format)
        vfprintf(stderr, format, ap);
    va_end(ap);

    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}

/* Usage / command-line errors */
__attribute__((noreturn)) void usageErr(const char *format, ...)
{
    va_list ap;
    fflush(stdout);
    fprintf(stderr, "Usage: ");
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}

__attribute__((noreturn)) void cmdLineErr(const char *format, ...)
{
    va_list ap;
    fflush(stdout);
    fprintf(stderr, "Command-line usage error: ");
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fputc('\n', stderr);
    exit(EXIT_FAILURE);
}