#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    time_t currentTime;
    struct tm *localTm;

    /* Get the current time */
    currentTime = time(NULL);
    if (currentTime == (time_t)-1)
    {
        perror("time");
        exit(EXIT_FAILURE);
    }

    /* Convert to local time representation */
    localTm = localtime(&currentTime);
    if (localTm == NULL)
    {
        perror("localtime");
        exit(EXIT_FAILURE);
    }

    /* Print the local time in a human-readable format */
    printf("Current local time: %s", asctime(localTm));

    return EXIT_SUCCESS;
}