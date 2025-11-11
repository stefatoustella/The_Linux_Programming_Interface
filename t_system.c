#include <string.h>
#include <sys/wait.h>
#include "print_wait_status.h"
#include "tlpi_hdr.h"

#define MAX_CMD_LEN 200

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    char str[MAX_CMD_LEN];
    int status;

    for (;;)
    {
        /* Read and execute a shell command */
        printf("Command: ");
        fflush(stdout);
        if (fgets(str, MAX_CMD_LEN, stdin) == NULL)
            break; /* end-of-file */

        /* Remove trailing newline, if present */
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n')
            str[len - 1] = '\0';

        /* Ignore empty lines */
        if (str[0] == '\0')
            continue;

        status = system(str);
        if (status == -1)
        {
            errMsg("system");
            continue;
        }

        printf("system() returned: status=0x%04x (%d,%d)\n",
               (unsigned int)status, status >> 8, status & 0xff);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
            printf("(Probably) could not invoke shell\n");
        else
            printWaitStatus(NULL, status);
    }

    exit(EXIT_SUCCESS);
}