#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    time_t t; /* Will hold the current time */

    /* Get current time. We can either:
       1. Pass NULL to get just the return value
       2. Pass &t to store the time in t
       Both ways work the same */
    t = time(NULL);
    if (t == -1)
    {
        perror("time");
        return EXIT_FAILURE;
    }

    printf("Current time (seconds since Epoch): %ld\n", (long)t);
    return EXIT_SUCCESS;
}