/* Demonstrate getppid() and parent-child relationship via fork(). */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t parent_pid = getpid();
    pid_t parent_ppid = getppid();

    printf("Original process: PID=%ld PPID=%ld\n", (long)parent_pid, (long)parent_ppid);

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        /* Child */
        printf("Child: PID=%ld, getppid()=%ld\n", (long)getpid(), (long)getppid());
        _exit(EXIT_SUCCESS);
    }
    else
    {
        /* Parent */
        printf("Parent: forked child PID=%ld\n", (long)pid);
        waitpid(pid, NULL, 0);
        printf("Parent: child has exited\n");
    }

    return EXIT_SUCCESS;
}