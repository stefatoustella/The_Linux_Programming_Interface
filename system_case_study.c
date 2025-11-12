/*
 * system_case_study.c -- case study using a local system() implementation
 */

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "tlpi_hdr.h"
#include "print_wait_status.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    const char *cmds[] = {
        NULL,                         /* test system(NULL) */
        "echo Hello, world",          /* normal exit (status 0) */
        "false",                      /* normal exit with nonzero status (1) */
        "nonexistentcommand",         /* shell can't find command -> exit 127 */
        "sh -c 'kill -s SIGSEGV $$'", /* child (shell) kills itself via SIGSEGV */
        "sh -c 'exit 42'"             /* child exits with status 42 */
    };
    const size_t ncmds = sizeof(cmds) / sizeof(cmds[0]);

    printf("=== system() case study ===\n\n");

    for (size_t i = 0; i < ncmds; ++i)
    {
        const char *cmd = cmds[i];

        if (cmd == NULL)
        {
            printf("Test: system(NULL) -> check for shell availability\n");
            int avail = system(NULL);
            if (avail == 0)
                printf("system(NULL) -> no shell available (returned 0)\n\n");
            else
                printf("system(NULL) -> shell appears available (returned %d)\n\n", avail);
            continue;
        }

        printf("Test: run command: %s\n", cmd);
        fflush(stdout);

        int status = system(cmd);
        if (status == -1)
        {
            /* system() reported an error (e.g., fork/exec/system error) */
            errMsg("system(\"%s\") failed", cmd);
            printf("\n");
            continue;
        }

        /* Print raw return value and decoded form using printWaitStatus */
        printf("system() returned raw status=0x%04x (%d,%d)\n",
               (unsigned int)status, status >> 8, status & 0xff);

        /* If shell could not be invoked, some implementations return 127 in high byte */
        if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
        {
            printf("(Probably) could not invoke shell (exit status 127)\n\n");
        }
        else
        {
            /* Use the helper to print a human-readable explanation */
            printWaitStatus("Decoded status: ", status);
            printf("\n");
        }
    }

    printf("=== done ===\n");
    return EXIT_SUCCESS;
}