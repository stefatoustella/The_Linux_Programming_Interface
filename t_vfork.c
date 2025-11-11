#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int istack = 222;
    switch (vfork())
    {
    case -1:
        errExit("vfork");
        /* Child executes first, in parent's memory space */
    case 0:
        /* Even if we sleep for a while,
               parent still is not scheduled */
        sleep(3);

        write(STDOUT_FILENO, "Child executing\n", 16);
        /* This change will be seen by parent */
        istack *= 3;

        _exit(EXIT_SUCCESS);
        /* Parent is blocked until child exits */
    default:

        write(STDOUT_FILENO, "Parent executing\n", 17);
        printf("istack=%d\n", istack);
        exit(EXIT_SUCCESS);
    }
}