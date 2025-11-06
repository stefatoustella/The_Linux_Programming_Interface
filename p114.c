/* Demonstrate getpid() and creating a process-unique filename. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(void)
{
    pid_t pid = getpid();
    printf("Process ID: %ld\n", (long)pid);

    char fname[64];
    int ret = snprintf(fname, sizeof(fname), "file-%ld.tmp", (long)pid);
    if (ret < 0 || ret >= (int)sizeof(fname))
    {
        fprintf(stderr, "Filename generation failed\n");
        return EXIT_FAILURE;
    }

    /* Create a process-unique file; fail if it already exists */
    int fd = open(fname, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("open");
        return EXIT_FAILURE;
    }

    char buf[128];
    int n = snprintf(buf, sizeof(buf), "This file was created by PID %ld\n", (long)pid);
    if (n > 0)
    {
        ssize_t w = write(fd, buf, (size_t)n);
        if (w == -1)
        {
            perror("write");
            close(fd);
            return EXIT_FAILURE;
        }
    }

    close(fd);
    printf("Created process-unique file: %s\n", fname);
    return EXIT_SUCCESS;
}