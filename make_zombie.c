#include <signal.h>
/* For basename() declaration */
#include <libgen.h>
#include "tlpi_hdr.h"

#define CMD_SIZE 200

int main(int argc, char *argv[])
{
    (void)argc; /* silence unused-parameter warning */

    char cmd[CMD_SIZE];
    pid_t childPid;

    /* Disable buffering of stdout */
    setbuf(stdout, NULL);

    printf("Parent PID=%ld\n", (long)getpid());

    switch (childPid = fork())
    {
    case -1:
        errExit("fork");
        /* Child: immediately exits to become zombie */
    case 0:

        printf("Child (PID=%ld) exiting\n", (long)getpid());
        _exit(EXIT_SUCCESS);

        /* Parent */
    default:
        /* Give child a chance to start and exit */
        sleep(3);
        snprintf(cmd, CMD_SIZE, "ps | grep %s", basename(argv[0]));
        /* Ensure string is null-terminated */
        cmd[CMD_SIZE - 1] = '\0';
        /* View zombie child */
        system(cmd);
        /* Now send the "sure kill" signal to the zombie */
        if (kill(childPid, SIGKILL) == -1)
            errMsg("kill");

        /* Give child a chance to react to signal */
        sleep(3);

        printf("After sending SIGKILL to zombie (PID=%ld):\n", (long)childPid);
        /* View zombie child again */
        system(cmd);

        exit(EXIT_SUCCESS);
    }
}