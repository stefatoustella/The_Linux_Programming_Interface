#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "become_daemon.h"
#include "tlpi_hdr.h"

int main(void)
{
    int fd;

    /* Become a daemon (use default behavior: umask(0), chdir("/"), close fds, reopen std fds) */
    if (becomeDaemon(0) == -1)
        errExit("becomeDaemon");

    /* Write PID file for verification (optional) */
    fd = open("/tmp/test_daemon.pid", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd != -1)
    {
        dprintf(fd, "%ld\n", (long)getpid());
        close(fd);
    }

    /* Simple daemon work: sleep and write a message to syslog-like file */
    for (int i = 0; i < 5; ++i)
    {
        /* Append a timestamped message to a file (since stdout/stderr point to /dev/null) */
        int logfd = open("/tmp/test_daemon.log", O_CREAT | O_APPEND | O_WRONLY, 0644);
        if (logfd != -1)
        {
            dprintf(logfd, "Daemon PID %ld alive, iteration %d\n", (long)getpid(), i);
            close(logfd);
        }
        sleep(2);
    }

    /* Cleanup: remove pid file */
    unlink("/tmp/test_daemon.pid");
    return 0;
}