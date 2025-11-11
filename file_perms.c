/*
 * file_perms.c
 *
 * Provides filePermStr(mode_t, int) which returns a static "rwxrwxrwx"
 * permission string.  To allow building this translation unit without
 * linking to other objects, a small test main() is included when the
 * FILE_PERMS_TEST macro is defined at compile time.
 *
 * Usage:
 *  - Compile only (no linker): gcc -Wall -Wextra -c file_perms.c -o file_perms.o
 *  - Build test executable:    gcc -Wall -Wextra -DFILE_PERMS_TEST file_perms.c -o test_file_perms
 */

#include <sys/stat.h>
#include <stdio.h>
#include "file_perms.h"

/* Provide a portable fallback if S_ISVTX isn't defined but __S_ISVTX is,
 * or if neither is available (define as 0 so code still compiles).
 */
#if !defined(S_ISVTX)
#if defined(__S_ISVTX)
#define S_ISVTX __S_ISVTX
#else
/* No sticky-bit macro available on this platform; define as 0 so code still compiles. */
#define S_ISVTX 0
#endif
#endif

/* 9 permission chars + terminating NUL */
#define STR_SIZE (9 + 1)

char *filePermStr(mode_t perm, int flags)
{
    static char str[STR_SIZE];

    snprintf(str, STR_SIZE,
             "%c%c%c%c%c%c%c%c%c",
             (perm & S_IRUSR) ? 'r' : '-',
             (perm & S_IWUSR) ? 'w' : '-',
             (perm & S_IXUSR)
                 ? ((perm & S_ISUID) && (flags & FP_SPECIAL) ? 's' : 'x')
                 : ((perm & S_ISUID) && (flags & FP_SPECIAL) ? 'S' : '-'),
             (perm & S_IRGRP) ? 'r' : '-',
             (perm & S_IWGRP) ? 'w' : '-',
             (perm & S_IXGRP)
                 ? ((perm & S_ISGID) && (flags & FP_SPECIAL) ? 's' : 'x')
                 : ((perm & S_ISGID) && (flags & FP_SPECIAL) ? 'S' : '-'),
             (perm & S_IROTH) ? 'r' : '-',
             (perm & S_IWOTH) ? 'w' : '-',
             (perm & S_IXOTH)
                 ? ((perm & S_ISVTX) && (flags & FP_SPECIAL) ? 't' : 'x')
                 : ((perm & S_ISVTX) && (flags & FP_SPECIAL) ? 'T' : '-'));

    return str;
}

#ifdef FILE_PERMS_TEST
/* Small test driver so you can build and run this file on its own:
 * gcc -DFILE_PERMS_TEST file_perms.c -o test_file_perms
 */
int main(void)
{
    mode_t m1 = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; /* 0644 */
    mode_t m2 = S_IRWXU | S_IRWXG | S_IRWXO;           /* 0777 */
    mode_t m3 = S_IRUSR | S_IWUSR | S_IXUSR | S_ISUID; /* 4755 - setuid */
    mode_t m4 = S_IRWXU | S_ISVTX;                     /* sticky bit example */

    printf("0644 -> %s\n", filePermStr(m1, FP_SPECIAL));
    printf("0777 -> %s\n", filePermStr(m2, 0));
    printf("4755 -> %s\n", filePermStr(m3, FP_SPECIAL));
    printf("sticky-> %s\n", filePermStr(m4, FP_SPECIAL));

    return 0;
}
#endif /* FILE_PERMS_TEST */