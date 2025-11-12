#define _POSIX_C_SOURCE 200809L
#include <unistd.h>   /* fork, chdir, close, sysconf, STD*_FILENO, _exit */
#include <sys/stat.h> /* umask */
#include <fcntl.h>    /* open flags */
#include <stdlib.h>   /* EXIT_SUCCESS */
#include <errno.h>    /* errno */
#include "become_daemon.h"
#include "tlpi_hdr.h"

/* Returns 0 on success, -1 on error (errno preserved) */
int becomeDaemon(int flags)
{
    int maxfd, fd;
    int savedErrno;

    /* 1) Fork and let parent exit so we run in background */
    switch (fork())
    {
    case -1:
        return -1;
    case 0:
        /* child continues */
        break;
    default:
        _exit(EXIT_SUCCESS);
    }

    /* 2) Become session leader to lose controlling terminal */
    if (setsid() == -1)
        return -1;

    /* 3) Fork again to ensure we are not session leader (prevents reacquiring a terminal) */
    switch (fork())
    {
    case -1:
        return -1;
    case 0:
        /* child continues */
        break;
    default:
        _exit(EXIT_SUCCESS);
    }

    /* 4) Set file mode creation mask to 0 unless caller asked not to */
    if (!(flags & BD_NO_UMASK0))
        umask(0);

    /* 5) Change to root directory unless caller asked not to */
    if (!(flags & BD_NO_CHDIR))
    {
        if (chdir("/") == -1)
            return -1;
    }

    /* 6) Close all open file descriptors unless caller asked not to */
    if (!(flags & BD_NO_CLOSE_FILES))
    {
        maxfd = sysconf(_SC_OPEN_MAX);
        if (maxfd == -1) /* indeterminate; use a conservative guess */
            maxfd = BD_MAX_CLOSE;
        for (fd = 0; fd < maxfd; ++fd)
            close(fd);
    }

    /* 7) Reopen standard file descriptors on /dev/null unless caller asked not to */
    if (!(flags & BD_NO_REOPEN_STD_FDS))
    {
        fd = open("/dev/null", O_RDWR);
        if (fd == -1)
            return -1;

        /* If open() did not return stdin fd (0), dup it there and close the original */
        if (fd != STDIN_FILENO)
        {
            if (dup2(fd, STDIN_FILENO) == -1)
            {
                savedErrno = errno;
                close(fd);
                errno = savedErrno;
                return -1;
            }
            close(fd);
        }

        /* Duplicate stdin to stdout and stderr */
        if (dup2(STDIN_FILENO, STDOUT_FILENO) == -1)
            return -1;
        if (dup2(STDIN_FILENO, STDERR_FILENO) == -1)
            return -1;
    }

    return 0;
}