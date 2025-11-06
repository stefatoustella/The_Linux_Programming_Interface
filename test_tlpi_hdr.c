#include <stdio.h>
#include "tlpi_hdr.h"

int main(void)
{
    int x = 5, y = 10;
    printf("MIN(%d, %d) = %d\n", x, y, MIN(x, y));
    printf("MAX(%d, %d) = %d\n", x, y, MAX(x, y));

    /* Side-effect test: if macros evaluate arguments more than once, a and b
       will be incremented twice. With the safe implementation they are
       incremented exactly once. */
    int a = 2, b = 3;
    int m = MIN(a++, b++);
    printf("After MIN(a++, b++): a=%d b=%d m=%d\n", a, b, m);

    return 0;
}
