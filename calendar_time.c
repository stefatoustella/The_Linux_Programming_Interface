#define _XOPEN_SOURCE
#include <locale.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SECONDS_IN_TROPICAL_YEAR (365.24219 * 24 * 60 * 60)

static void errExit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    (void)argc; /* Suppress unused parameter warning */
    (void)argv;

    time_t current_time;
    struct tm *gm_time_ptr, *local_time_ptr;
    struct tm gm_time, local_time;
    struct timeval tv;

    /* Get current time */
    current_time = time(NULL);
    if (current_time == -1)
        errExit("time");

    printf("Seconds since the Epoch (1 Jan 1970): %ld", (long)current_time);
    printf(" (about %6.3f years)\n", current_time / SECONDS_IN_TROPICAL_YEAR);

    /* Get high-resolution time */
    if (gettimeofday(&tv, NULL) == -1)
        errExit("gettimeofday");
    printf("gettimeofday() returned %ld secs, %ld microsecs\n",
           (long)tv.tv_sec, (long)tv.tv_usec);

    /* Get UTC time */
    gm_time_ptr = gmtime(&current_time);
    if (gm_time_ptr == NULL)
        errExit("gmtime");

    /* Save local copy to prevent modification by other time functions */
    gm_time = *gm_time_ptr;
    /* Display UTC (gmtime) time components */
    printf("\nBroken down by gmtime() (UTC):\n");
    printf(" year=%d mon=%d mday=%d hour=%d min=%d sec=%d ",
           gm_time.tm_year + 1900, gm_time.tm_mon + 1, gm_time.tm_mday,
           gm_time.tm_hour, gm_time.tm_min, gm_time.tm_sec);
    printf("wday=%d yday=%d isdst=%d\n",
           gm_time.tm_wday, gm_time.tm_yday, gm_time.tm_isdst);

    /* Get local time */
    local_time_ptr = localtime(&current_time);
    if (local_time_ptr == NULL)
        errExit("localtime");

    /* Save local copy */
    local_time = *local_time_ptr;

    /* Display local time components */
    printf("\nBroken down by localtime() (local time):\n");
    printf(" year=%d mon=%d mday=%d hour=%d min=%d sec=%d ",
           local_time.tm_year + 1900, local_time.tm_mon + 1, local_time.tm_mday,
           local_time.tm_hour, local_time.tm_min, local_time.tm_sec);
    printf("wday=%d yday=%d isdst=%d\n",
           local_time.tm_wday, local_time.tm_yday, local_time.tm_isdst);

    /* Format times using various functions */
    printf("\nFormatted times:\n");
    printf("asctime() formats the gmtime() value as:    %s", asctime(&gm_time));
    printf("ctime() formats the time() value as:        %s", ctime(&current_time));

    /* Convert broken-down time back to time_t */
    printf("\nTime conversions:\n");
    printf("mktime() of gmtime() value:    %ld secs\n", (long)mktime(&gm_time));
    printf("mktime() of localtime() value: %ld secs\n", (long)mktime(&local_time));

    return EXIT_SUCCESS;
}