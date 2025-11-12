/*
 * Replacement implementation of system(). NOTE: defining a function
 * named 'system' will override/replace the libc system() symbol when
 * linked into the same program. If you do not intend to replace libc's
 * implementation, rename this to e.g. my_system().
 *
 * This implementation follows the usual semantics:
 *  - If command == NULL: return non-zero if a shell is available.
 *  - Otherwise: fork, exec /bin/sh -c command in child, parent waits.
 *
 * Uses sigaction/sigprocmask to temporarily ignore SIGINT/SIGQUIT and
 * block SIGCHLD while creating the child, restoring prior dispositions
 * and mask before returning.
 */

#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

/* If you want to avoid replacing libc's system(), rename this function. */
int system(const char *command)
{
    sigset_t blockMask, origMask;
    struct sigaction saIgnore, saOrigQuit, saOrigInt, saDefault;
    pid_t childPid;
    int status, savedErrno;

    /* If command is NULL, return nonzero if a shell is available. */
    if (command == NULL)
    {
        /* Test whether /bin/sh is executable */
        return (access("/bin/sh", X_OK) == 0) ? 1 : 0;
    }

    /* Block SIGCHLD while we set up and fork */
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &blockMask, &origMask);

    /* Ignore SIGINT and SIGQUIT in parent during the fork/exec */
    saIgnore.sa_handler = SIG_IGN;
    saIgnore.sa_flags = 0;
    sigemptyset(&saIgnore.sa_mask);
    sigaction(SIGINT, &saIgnore, &saOrigInt);
    sigaction(SIGQUIT, &saIgnore, &saOrigQuit);

    switch (childPid = fork())
    {
    case -1:
        /* fork failed */
        status = -1;
        break;

    case 0:
    {
        /* Child: restore default handlers for SIGINT/SIGQUIT if they were not ignored. */
        saDefault.sa_handler = SIG_DFL;
        saDefault.sa_flags = 0;
        sigemptyset(&saDefault.sa_mask);

        if (saOrigInt.sa_handler != SIG_IGN)
            sigaction(SIGINT, &saDefault, NULL);
        if (saOrigQuit.sa_handler != SIG_IGN)
            sigaction(SIGQUIT, &saDefault, NULL);

        /* Restore original signal mask */
        sigprocmask(SIG_SETMASK, &origMask, NULL);

        /* Execute the shell to run the command. If execl fails, _exit(127). */
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        _exit(127);
        break;
    }

    default:
        /* Parent: wait for child to terminate. Retry if waitpid was interrupted. */
        while (waitpid(childPid, &status, 0) == -1)
        {
            if (errno != EINTR)
            {
                status = -1;
                break;
            }
        }
        break;
    }

    /* Restore errno-safe state: save errno, restore masks and actions, then restore errno */
    savedErrno = errno;
    sigprocmask(SIG_SETMASK, &origMask, NULL);
    sigaction(SIGINT, &saOrigInt, NULL);
    sigaction(SIGQUIT, &saOrigQuit, NULL);
    errno = savedErrno;

    return status;
}