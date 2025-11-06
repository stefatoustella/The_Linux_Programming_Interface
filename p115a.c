/* Demonstrate orphaned child reparenting to init (PID 1).
 * Parent exits immediately after fork; child sleeps long enough so that
 * the parent terminates and the child is adopted by init. The child
 * prints its parent PID (getppid()) before and after reparenting.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid > 0)
    {
        /* Parent: exit immediately so child becomes orphan */
        printf("Parent (PID=%ld) exiting immediately\n", (long)getpid());
        fflush(stdout);
        _exit(EXIT_SUCCESS);
    }

    /* Child */
    printf("Child: PID=%ld, initial getppid()=%ld\n", (long)getpid(), (long)getppid());
    fflush(stdout);

    /* Sleep long enough for the parent to exit and for the child to be
     * reparented to init (PID 1). On many systems init is PID 1 (systemd
     * or /sbin/init). We poll getppid() until it becomes 1 (or a short
     * timeout occurs).
     */
    for (int i = 0; i < 10; ++i)
    {
        sleep(1);
        pid_t pp = getppid();
        printf("Child: after %d s, getppid()=%ld\n", i + 1, (long)pp);
        fflush(stdout);
        if (pp == 1)
        {
            printf("Child: now reparented to init (PID 1)\n");
            fflush(stdout);
            break;
        }
    }

    return EXIT_SUCCESS;
}
