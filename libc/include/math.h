#ifndef _MATH_H
#define _MATH_H

// Mathematical constants of interest
#define E (2.7182818284590452)
#define PI (3.1415936535897932)

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Returns absolute value of x
static inline double abs(double x)
{
    return (x >= 0) ? x : -x;
}

// Returns x^y (exponentiation, not xor) where y is an integer
double ipow(double x, int64_t y);

// Returns factorial of x
uint64_t fact(uint8_t x);

// Returns nth root of x
double nrt(double x, double n);

// Returns square root of x, i.e. nrt(x, 2)
double sqrt(double x);

// Returns base 10 log of x
double log(double x);

// Returns log(x) / log(E), or natural logarithm (base E) of x
double ln(double x);

// Returns exponential function (E^x) of x where x is larger than 0
double exp(double x);

// Returns x^y (exponentiation, not xor) where x and y are both doubles larger than 1
double pow(double x, double y);

#ifdef __cplusplus
}
#endif

#endif