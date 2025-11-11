/* Fixed t_fork.c - self-contained so it links and compiles without TLPI support files */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

/* Allocated in data segment */
static int idata = 111;

/* Minimal errExit implementation so we don't depend on TLPI support files */
static void errExit(const char *msg)
{
    if (msg && *msg)
        fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    else
        fprintf(stderr, "%s\n", strerror(errno));
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    /* Allocated in stack segment */
    int istack = 222;
    pid_t childPid;

    switch (childPid = fork())
    {
    case -1:
        errExit("fork");

    case 0:
        idata *= 3;
        istack *= 3;
        break;
    default:
        /* Give child a chance to execute */
        sleep(3);
        break;
    }

    /* Both parent and child come here */
    printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(),
           (childPid == 0) ? "(child) " : "(parent)", idata, istack);

    exit(EXIT_SUCCESS);
}