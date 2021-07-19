#ifndef _MATH_H
#define _MATH_H

#ifdef __cplusplus
extern "C" {
#endif

// Returns absolute value of x
static inline int abs(int x)
{
    return (x >= 0) ? x : -x;
}

#ifdef __cplusplus
}
#endif

#endif