/*
 * mem_segments.c
 *
 * Demonstrate typical memory segments used by a C program:
 *  - text (code) segment: compiled program instructions
 *  - initialized data segment: globals/static with initializers
 *  - uninitialized data segment (BSS): globals/static without initializers
 *  - heap: memory returned by malloc()
 *  - stack: automatic (local) variables
 *
 * Note: optimizing compilers and some ABIs may keep values in registers or
 * otherwise change where values live; compile with -O0 if you want to see
 * the straightforward mapping between C variables and segments.
 */

#include <stdio.h>
#include <stdlib.h>

/* Uninitialized data segment (BSS) */
char globBuf[65536];

/* Initialized data segment */
int primes[] = {2, 3, 5, 7};

/* A simple function in the text (code) segment */
static int
square(int x)
{
    int result; /* allocated in stack frame for square() */

    result = x * x;
    return result; /* return value typically passed in a register */
}

/* Do some calculations and print results */
static void
doCalc(int val)
{
    int t; /* allocated in stack frame for doCalc() */

    printf("The square of %d is %d\n", val, square(val));

    /* Do a small conditional allocation on the stack */
    if (val < 1000)
    {
        int i;
        for (i = 0; i < 1; ++i)
            ;
    }

    t = val * val * val;
    printf("The cube of %d is %d\n", val, t);
}

int main(int argc, char *argv[])
{
    /* Initialized data segment (static local) */
    static int key = 9973;

    /* Uninitialized data (large BSS object) */
    static char mbuf[1024 * 1024];

    char *p;   /* local variable allocated on the stack */
    int local; /* another stack variable used for printing address */

    /* Allocate memory on the heap */
    p = malloc(1024);
    if (p == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    /* Print addresses to demonstrate where objects live */
    printf("Address of square() (text): %p\n", (void *)square);
    printf("Address of primes (data): %p\n", (void *)primes);
    printf("Address of key (data): %p\n", (void *)&key);
    printf("Address of globBuf (BSS): %p\n", (void *)globBuf);
    printf("Address of mbuf (BSS): %p\n", (void *)mbuf);
    printf("Heap via malloc(): %p\n", (void *)p);
    printf("Address of local (stack): %p\n", (void *)&local);

    doCalc(key);

    free(p);
    exit(EXIT_SUCCESS);
}