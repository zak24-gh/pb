#ifndef _MATH_H
#define _MATH_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Returns absolute value of x
static inline double abs(int x)
{
    return (x >= 0) ? x : -x;
}

double ipow(double x, int64_t y);

uint64_t fact(uint8_t x);

double nrt(double x, double n);

double sqrt(double x);

double log(double x);

double ln(double x);

double exp(double x);

double pow(double x, double y);

#ifdef __cplusplus
}
#endif

#endif