#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "tlpi_hdr.h"
#include "error_functions.h"
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
/* Allow "cc -D" to override definition */
int main(int argc, char *argv[])
{
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];
    struct stat statBuf1, statBuf2;
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s old-file new-file\n", argv[0]);
    /* Open input file */
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        errExit("opening file %s", argv[1]);

    /* If destination exists, check it's not the same file as source */
    if (stat(argv[2], &statBuf2) == 0)
    {
        if (fstat(inputFd, &statBuf1) == -1)
            errExit("fstat");
        if (statBuf1.st_dev == statBuf2.st_dev && statBuf1.st_ino == statBuf2.st_ino)
            fatal("%s and %s are the same file", argv[1], argv[2]);
    }
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;
    /* rw-rw-rw- */
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1)
        errExit("opening file %s", argv[2]);
    /* Transfer data until we encounter end of input or an error */
    while ((numRead = read(inputFd, buf, BUF_SIZE)) != 0)
    {
        if (numRead == -1)
        {
            if (errno == EINTR)
                continue; /* restart read */
            errExit("read");
        }

        /* Handle partial writes */
        ssize_t numWritten = 0;
        ssize_t numToWrite = numRead;
        char *outPtr = buf;

        while (numToWrite > 0)
        {
            numWritten = write(outputFd, outPtr, (size_t)numToWrite);
            if (numWritten == -1)
            {
                if (errno == EINTR)
                    continue; /* retry write */
                errExit("write");
            }
            numToWrite -= numWritten;
            outPtr += numWritten;
        }
    }
    if (close(inputFd) == -1)
        errExit("close input");
    if (close(outputFd) == -1)
        errExit("close output");
    exit(EXIT_SUCCESS);
}
