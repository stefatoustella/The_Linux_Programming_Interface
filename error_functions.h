#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

/*
 * error_functions.h
 * Small helper prototypes for error-reporting functions used in TLPI
 * examples. This header is C and C++ friendly and provides a portable
 * NORETURN macro that prefers C11's _Noreturn when available and falls
 * back to the GCC/Clang noreturn attribute.
 */

#ifdef __cplusplus
extern "C"
{
#endif

    /* Prototype for a nonfatal error message (does not exit) */
    void errMsg(const char *format, ...);

/* NORETURN handling: different compilers support different forms. Use a
 * prefix macro (NORETURN_PREFIX) for C11's _Noreturn, and a suffix macro
 * (NORETURN_SUFFIX) for GCC/Clang __attribute__((noreturn)). This lets
 * us write declarations that work with either mechanism.
 */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
/* C11: _Noreturn is a prefix specifier */
#define NORETURN_PREFIX _Noreturn
#define NORETURN_SUFFIX
#elif defined(__GNUC__) || defined(__clang__)
/* GCC/Clang: use attribute as a suffix */
#define NORETURN_PREFIX
#define NORETURN_SUFFIX __attribute__((__noreturn__))
#else
#define NORETURN_PREFIX
#define NORETURN_SUFFIX
#endif

    /* Prototypes for functions that terminate the program */
    NORETURN_PREFIX void errExit(const char *format, ...) NORETURN_SUFFIX;
    NORETURN_PREFIX void err_exit(const char *format, ...) NORETURN_SUFFIX; /* legacy alias */
    NORETURN_PREFIX void errExitEN(int errnum, const char *format, ...) NORETURN_SUFFIX;
    NORETURN_PREFIX void fatal(const char *format, ...) NORETURN_SUFFIX;
    NORETURN_PREFIX void usageErr(const char *format, ...) NORETURN_SUFFIX;
    NORETURN_PREFIX void cmdLineErr(const char *format, ...) NORETURN_SUFFIX;

#ifdef __cplusplus
}
#endif

#endif /* ERROR_FUNCTIONS_H */