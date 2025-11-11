/* Small test driver for printWaitStatus() */
#include "tlpi_hdr.h"
#include "print_wait_status.h"
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();
    if (pid == -1)
        errExit("fork");

    if (pid == 0)
    { /* child */
        /* Exit with status 7 so parent can inspect WIFEXITED/WEXITSTATUS */
        _exit(7);
    }
    else
    { /* parent */
        int status;
        if (waitpid(pid, &status, 0) == -1)
            errExit("waitpid");
        printWaitStatus("waitpid returned: ", status);
    }
    return 0;
}