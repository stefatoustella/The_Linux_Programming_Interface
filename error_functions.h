#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

/*
 * error_functions.h
 * Small helper prototypes for error-reporting functions used in TLPI
 * examples. C / C++ friendly. Provides NORETURN macros and optional
 * printf-format checking when compiled with GCC/Clang.
 */

#ifdef __cplusplus
extern "C"
{
#endif

/* NORETURN handling */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#define NORETURN_PREFIX _Noreturn
#define NORETURN_SUFFIX
#elif defined(__GNUC__) || defined(__clang__)
#define NORETURN_PREFIX
#define NORETURN_SUFFIX __attribute__((__noreturn__))
#else
#define NORETURN_PREFIX
#define NORETURN_SUFFIX
#endif

/* printf-style format attribute for GCC/Clang */
#if defined(__GNUC__) || defined(__clang__)
#define PRINTF_FMT(a, b) __attribute__((format(printf, a, b)))
#else
#define PRINTF_FMT(a, b)
#endif

    /* Prototype for a nonfatal error message (does not exit) */
    void errMsg(const char *format, ...) PRINTF_FMT(1, 2);

    /* Prototypes for functions that terminate the program */
    NORETURN_PREFIX void errExit(const char *format, ...) NORETURN_SUFFIX PRINTF_FMT(1, 2);
    NORETURN_PREFIX void err_exit(const char *format, ...) NORETURN_SUFFIX PRINTF_FMT(1, 2); /* legacy alias */
    /* errExitEN takes an explicit errno first, so format is argument 2 */
    NORETURN_PREFIX void errExitEN(int errnum, const char *format, ...) NORETURN_SUFFIX PRINTF_FMT(2, 3);
    NORETURN_PREFIX void fatal(const char *format, ...) NORETURN_SUFFIX PRINTF_FMT(1, 2);
    NORETURN_PREFIX void usageErr(const char *format, ...) NORETURN_SUFFIX PRINTF_FMT(1, 2);
    NORETURN_PREFIX void cmdLineErr(const char *format, ...) NORETURN_SUFFIX PRINTF_FMT(1, 2);

#ifdef __cplusplus
}
#endif

#endif /* ERROR_FUNCTIONS_H */