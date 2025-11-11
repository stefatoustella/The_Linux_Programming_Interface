/* Define POSIX feature test macro before any system headers so mkstemp is declared */
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    int fd, flags;
    char template[] = "/tmp/testXXXXXX";

    /* ... rest of your file unchanged ... */
    fd = mkstemp(template);
    if (fd == -1)
        errExit("mkstemp");

    printf("File offset before fork(): %lld\n",
           (long long)lseek(fd, 0, SEEK_CUR));
    flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        errExit("fcntl - F_GETFL");
    printf("O_APPEND flag before fork() is: %s\n",
           (flags & O_APPEND) ? "on" : "off");

    switch (fork())
    {
    case -1:
        errExit("fork");
    case 0:
        /* Child: change file offset and status flags */
        if (lseek(fd, 1000, SEEK_SET) == -1)
            errExit("lseek");
        /* Fetch current flags */
        flags = fcntl(fd, F_GETFL);
        if (flags == -1)
            errExit("fcntl - F_GETFL");
        /* Turn O_APPEND on */
        flags |= O_APPEND;
        if (fcntl(fd, F_SETFL, flags) == -1)
            errExit("fcntl - F_SETFL");
        _exit(EXIT_SUCCESS);
        /* Parent: can see file changes made by child */
    default:
        if (wait(NULL) == -1)
            /* Wait for child exit */
            errExit("wait");

        printf("Child has exited\n");
        printf("File offset in parent: %lld\n",
               (long long)lseek(fd, 0, SEEK_CUR));
        flags = fcntl(fd, F_GETFL);
        if (flags == -1)
            errExit("fcntl - F_GETFL");
        printf("O_APPEND flag in parent is: %s\n",
               (flags & O_APPEND) ? "on" : "off");
        exit(EXIT_SUCCESS);
    }
}