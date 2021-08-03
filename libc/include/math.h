#ifndef _MATH_H
#define _MATH_H

#define E (2.7182818284590452)
#define PI (3.1415936535897932)

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline double abs(double x)
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