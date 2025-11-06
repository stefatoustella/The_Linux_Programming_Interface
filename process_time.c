#include <sys/times.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Display 'msg' and process times */
static void displayProcessTimes(const char *msg)
{
    struct tms t;
    clock_t clockTime;
    static long clockTicks = 0;

    if (msg != NULL)
        printf("\n%s\n", msg);

    /* Fetch clock ticks on first call */
    if (clockTicks == 0)
    {
        clockTicks = sysconf(_SC_CLK_TCK);
        if (clockTicks == -1)
        {
            perror("sysconf");
            exit(EXIT_FAILURE);
        }
    }

    /* Get process times using clock() */
    clockTime = clock();
    if (clockTime == -1)
    {
        perror("clock");
        exit(EXIT_FAILURE);
    }

    printf("clock() returns: %ld clocks-per-sec (%.2f secs)\n",
           (long)clockTime, (double)clockTime / CLOCKS_PER_SEC);

    /* Get process times using times() */
    if (times(&t) == -1)
    {
        perror("times");
        exit(EXIT_FAILURE);
    }

    printf("Process times:\n");
    printf("  User CPU time:        %.2f secs\n",
           (double)t.tms_utime / clockTicks);
    printf("  System CPU time:      %.2f secs\n",
           (double)t.tms_stime / clockTicks);
    printf("  Child User CPU time:  %.2f secs\n",
           (double)t.tms_cutime / clockTicks);
    printf("  Child System CPU time:%.2f secs\n",
           (double)t.tms_cstime / clockTicks);
}

int main(int argc, char *argv[])
{
    int numCalls;

    /* Show clock information */
    printf("System Information:\n");
    printf("CLOCKS_PER_SEC = %ld\n", (long)CLOCKS_PER_SEC);
    printf("Clock ticks/sec = %ld\n\n", sysconf(_SC_CLK_TCK));

    /* Get number of iterations from command line or use default */
    numCalls = (argc > 1) ? atoi(argv[1]) : 100000000;
    if (numCalls <= 0)
    {
        fprintf(stderr, "Number of calls must be > 0\n");
        exit(EXIT_FAILURE);
    }

    displayProcessTimes("At program start:");

    /* Do some CPU-intensive work using getppid() */
    printf("\nExecuting getppid() %d times...\n", numCalls);
    for (int j = 0; j < numCalls; j++)
    {
        (void)getppid(); /* Cast to void to suppress unused result warning */
    }

    displayProcessTimes("After getppid() loop:");

    /* Create a child process to demonstrate child times */
    pid_t childPid = fork();
    if (childPid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (childPid == 0)
    { /* Child process */
        /* Do some work in child */
        for (int j = 0; j < numCalls / 2; j++)
        {
            (void)getppid();
        }
        exit(EXIT_SUCCESS);
    }
    else
    { /* Parent process */
        /* Wait for child to finish */
        if (wait(NULL) == -1)
        {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        displayProcessTimes("After child process:");
    }

    return EXIT_SUCCESS;
}