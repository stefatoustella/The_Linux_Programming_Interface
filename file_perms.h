#ifndef FILE_PERMS_H
#define FILE_PERMS_H

#include <sys/types.h>
#include <sys/stat.h> /* Provide S_IRUSR, S_ISVTX, etc. and ensure mode-related macros available */

#ifdef __cplusplus
extern "C"
{
#endif

#define FP_SPECIAL 1

    /* Include set-user-ID, set-group-ID, and sticky bit info in returned string */
    char *filePermStr(mode_t mode, int flags);

#ifdef __cplusplus
}
#endif

#endif /* FILE_PERMS_H */