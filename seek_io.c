#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "tlpi_hdr.h"
#include "error_functions.h"
int main(int argc, char *argv[])
{
    size_t len;
    off_t offset;
    int fd, ap, j;
    char *buf;
    ssize_t numRead;
    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n",
                 argv[0]);
    fd = open(argv[1], O_RDWR | O_CREAT,
              S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                  S_IROTH | S_IWOTH);
    /* rw-rw-rw- */
    if (fd == -1)
        errExit("open");
    for (ap = 2; ap < argc; ap++)
    {
        switch (argv[ap][0])
        {
        case 'r':
            /* Display bytes at current offset, as text */
        case 'R':
            /* Display bytes at current offset, in hex */
            {
                char *endptr;
                long long rval = strtoll(&argv[ap][1], &endptr, 0);
                if (endptr == &argv[ap][1] || *endptr != '\0' || rval < 0)
                    cmdLineErr("Invalid length: %s\n", argv[ap]);
                len = (size_t)rval;
            }

            if (len == 0)
            {
                printf("%s: zero length\n", argv[ap]);
                break;
            }

            buf = malloc(len);
            if (buf == NULL)
                errExit("malloc");

            for (;;)
            {
                numRead = read(fd, buf, len);
                if (numRead == -1)
                {
                    if (errno == EINTR)
                        continue;
                    errExit("read");
                }
                break;
            }

            if (numRead == 0)
            {
                printf("%s: end-of-file\n", argv[ap]);
            }
            else
            {
                printf("%s: ", argv[ap]);
                for (j = 0; j < numRead; j++)
                {
                    unsigned char uc = (unsigned char)buf[j];
                    if (argv[ap][0] == 'r')
                        printf("%c", isprint(uc) ? uc : '?');
                    else
                        printf("%02x ", (unsigned int)uc);
                }
                printf("\n");
            }
            free(buf);
            break;
        case 'w':
            /* Write string at current offset */
            {
                const char *str = &argv[ap][1];
                size_t toWrite = strlen(str);
                size_t written = 0;

                while (written < toWrite)
                {
                    ssize_t w = write(fd, str + written, toWrite - written);
                    if (w == -1)
                    {
                        if (errno == EINTR)
                            continue;
                        errExit("write");
                    }
                    written += (size_t)w;
                }

                printf("%s: wrote %zu bytes\n", argv[ap], written);
            }
            break;
        case 's':
            /* Change file offset */
            {
                char *endptr;
                long long rval = strtoll(&argv[ap][1], &endptr, 0);
                if (endptr == &argv[ap][1] || *endptr != '\0')
                    cmdLineErr("Invalid offset: %s\n", argv[ap]);
                offset = (off_t)rval;
            }
            if (lseek(fd, offset, SEEK_SET) == -1)
                errExit("lseek");
            printf("%s: seek succeeded\n", argv[ap]);
            break;
        default:
            cmdLineErr("Argument must start with [rRws]: %s\n", argv[ap]);
        }
    }
    exit(EXIT_SUCCESS);
}