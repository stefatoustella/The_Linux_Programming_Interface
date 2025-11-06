#include <stdio.h>
#include <gnu/libc-version.h>
#include "tlpi_hdr.h"

int main(void)
{
    /* Print the glibc version */
    printf("glibc version: %s\n", gnu_get_libc_version());

    /* Demonstrate MIN / MAX macros */
    int x = 5, y = 10;
    printf("MIN(%d, %d) = %d\n", x, y, MIN(x, y));
    printf("MAX(%d, %d) = %d\n", x, y, MAX(x, y));

    /* Side-effect safety test */
    int a = 2, b = 3;
    int m = MIN(a++, b++);
    printf("After MIN(a++, b++): a=%d b=%d m=%d\n", a, b, m);

    return 0;
}