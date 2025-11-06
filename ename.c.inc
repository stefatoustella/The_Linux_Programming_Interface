/* ename.c.inc
 *
 * Provides an array `ename[]` indexed by errno values that contains the
 * symbolic errno macro names (for example, "ENOENT"). This file is intended
 * to be included from a C source file when symbolic names are desired.
 *
 * The array uses designated initializers where available; entries for errno
 * values not present on the platform are simply left unset.
 */

#include <errno.h>

#ifndef ENAME_MAX
#define ENAME_MAX 256
#endif

const char *ename[ENAME_MAX] = {
    [0] = "0",
#ifdef EPERM
    [EPERM] = "EPERM",
#endif
#ifdef ENOENT
    [ENOENT] = "ENOENT",
#endif
#ifdef ESRCH
    [ESRCH] = "ESRCH",
#endif
#ifdef EINTR
    [EINTR] = "EINTR",
#endif
#ifdef EIO
    [EIO] = "EIO",
#endif
#ifdef ENXIO
    [ENXIO] = "ENXIO",
#endif
#ifdef E2BIG
    [E2BIG] = "E2BIG",
#endif
#ifdef ENOEXEC
    [ENOEXEC] = "ENOEXEC",
#endif
#ifdef EBADF
    [EBADF] = "EBADF",
#endif
#ifdef ECHILD
    [ECHILD] = "ECHILD",
#endif
#ifdef EAGAIN
    [EAGAIN] = "EAGAIN",
#endif
#ifdef ENOMEM
    [ENOMEM] = "ENOMEM",
#endif
#ifdef EACCES
    [EACCES] = "EACCES",
#endif
#ifdef EFAULT
    [EFAULT] = "EFAULT",
#endif
#ifdef EBUSY
    [EBUSY] = "EBUSY",
#endif
#ifdef EEXIST
    [EEXIST] = "EEXIST",
#endif
#ifdef EXDEV
    [EXDEV] = "EXDEV",
#endif
#ifdef ENODEV
    [ENODEV] = "ENODEV",
#endif
#ifdef ENOTDIR
    [ENOTDIR] = "ENOTDIR",
#endif
#ifdef EISDIR
    [EISDIR] = "EISDIR",
#endif
#ifdef EINVAL
    [EINVAL] = "EINVAL",
#endif
#ifdef ENFILE
    [ENFILE] = "ENFILE",
#endif
#ifdef EMFILE
    [EMFILE] = "EMFILE",
#endif
#ifdef ENOTTY
    [ENOTTY] = "ENOTTY",
#endif
#ifdef EFBIG
    [EFBIG] = "EFBIG",
#endif
#ifdef ENOSPC
    [ENOSPC] = "ENOSPC",
#endif
#ifdef ESPIPE
    [ESPIPE] = "ESPIPE",
#endif
#ifdef EROFS
    [EROFS] = "EROFS",
#endif
#ifdef EMLINK
    [EMLINK] = "EMLINK",
#endif
#ifdef EPIPE
    [EPIPE] = "EPIPE",
#endif
#ifdef EDOM
    [EDOM] = "EDOM",
#endif
#ifdef ERANGE
    [ERANGE] = "ERANGE",
#endif
#ifdef EDEADLK
    [EDEADLK] = "EDEADLK",
#endif
#ifdef ENAMETOOLONG
    [ENAMETOOLONG] = "ENAMETOOLONG",
#endif
#ifdef ENOLCK
    [ENOLCK] = "ENOLCK",
#endif
#ifdef ENOSYS
    [ENOSYS] = "ENOSYS",
#endif
#ifdef ENOTEMPTY
    [ENOTEMPTY] = "ENOTEMPTY",
#endif
#ifdef ELOOP
    [ELOOP] = "ELOOP",
#endif
#ifdef ENOMSG
    [ENOMSG] = "ENOMSG",
#endif
#ifdef EIDRM
    [EIDRM] = "EIDRM",
#endif
#ifdef ENODATA
    [ENODATA] = "ENODATA",
#endif
#ifdef ETIME
    [ETIME] = "ETIME",
#endif
#ifdef ENOSR
    [ENOSR] = "ENOSR",
#endif
#ifdef ENOLINK
    [ENOLINK] = "ENOLINK",
#endif
#ifdef EPROTO
    [EPROTO] = "EPROTO",
#endif
#ifdef EPROTONOSUPPORT
    [EPROTONOSUPPORT] = "EPROTONOSUPPORT",
#endif
#ifdef ESOCKTNOSUPPORT
    [ESOCKTNOSUPPORT] = "ESOCKTNOSUPPORT",
#endif
#ifdef EOPNOTSUPP
    [EOPNOTSUPP] = "EOPNOTSUPP",
#endif
#ifdef ENETDOWN
    [ENETDOWN] = "ENETDOWN",
#endif
#ifdef ENETUNREACH
    [ENETUNREACH] = "ENETUNREACH",
#endif
#ifdef ENETRESET
    [ENETRESET] = "ENETRESET",
#endif
#ifdef ECONNABORTED
    [ECONNABORTED] = "ECONNABORTED",
#endif
#ifdef ECONNRESET
    [ECONNRESET] = "ECONNRESET",
#endif
#ifdef ENOBUFS
    [ENOBUFS] = "ENOBUFS",
#endif
#ifdef ESHUTDOWN
    [ESHUTDOWN] = "ESHUTDOWN",
#endif
#ifdef ETIMEDOUT
    [ETIMEDOUT] = "ETIMEDOUT",
#endif
#ifdef ECONNREFUSED
    [ECONNREFUSED] = "ECONNREFUSED",
#endif
#ifdef EHOSTUNREACH
    [EHOSTUNREACH] = "EHOSTUNREACH",
#endif
#ifdef EALREADY
    [EALREADY] = "EALREADY",
#endif
#ifdef EINPROGRESS
    [EINPROGRESS] = "EINPROGRESS",
#endif
#ifdef EDQUOT
    [EDQUOT] = "EDQUOT",
#endif
};

#define MAX_ENAME (ENAME_MAX - 1)
