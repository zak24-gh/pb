#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// abort specialized for libk
__attribute__((__noreturn__))
void abortk(void)
{
    // Add panic later
    puts("kernel: panic: abort");

    while (true) {}
    __builtin_unreachable();
}