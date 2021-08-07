#include <stdint.h>
#include <limits.h>
#include <math.h>

// Mathematical constants of interest also defined here
#define E (2.7182818284590452)
#define PI (3.1415936535897932)

double ipow_hlpr(double x, uint64_t y)
{
    double power = 1;
    
    // Multiplies power by x a total of y times. If y is 0, power will be 1.
    for (int i = 0; i < y; i++)
        power *= x;
        
    return power;
}

double ipow(double x, int64_t y)
{
    double power = 0;

    // ipow_hlpr with support for negative integer exponents, not supported by normal pow()
    if (y > 0)
        power = ipow_hlpr(x, y);
    else if (y < 0)
        power = 1 / (double) ipow_hlpr(x, abs(y));
    else
        power = 1;

    return power;   
}

uint64_t fact(uint8_t x)
{
    uint64_t _fact = 1;
    
    // Multiples _fact by all numbers up to x and returns _fact
    for (uint8_t i = 1; i <= x; i++)
        _fact *= i;
        
    return _fact;
}

double nrt(double x, double n)
{
	double _nrt = 0;
	double current = 1;
	const double epsilon = 0.0000000000000001;
    double diff = INT_MAX;
    double prev = 1;

	if (x < 0)
		return -1;

    /* This algorithm can produce nth roots within an accuracy
    range of a predefined constant epsilon. (As of 0.0.0.9) this
    could be useful for some exponents under 1; however, this has
    not been tested yet. */
	while (diff >= epsilon)
	{
		current = (((n - 1) * prev) + ((double) x / ipow(prev, n - 1))) / (double) n;
        diff = abs(current - prev);
        prev = current;
	}
	_nrt = current;
	
	return _nrt;
}

double sqrt(double x)
{
    // Nth root of x when n is 2 is square root of x
	return nrt(x, 2);
}

double log_hlpr(double x)
{
    double current = x;
    double temp = current;
    double ans = 0;
    uint8_t digit = 0;

    /* This algorithm can reproduce the base 10 logarithm of any
    value greater than 1 up to 16 digits. It has already been
    implemented in log() as a means of finding logarithms of values
    smaller than 1. */
    for (int i = 0; i < 17; i++)
    {
        while (current > 1)
        {
            current /= 10;
            digit++;
        }
        
        if (digit)
            digit--;

        ans += (double) (digit / ipow(10, i));
        current = ipow((double) (temp / ipow(10, digit)), 10);
        temp = current;
        digit = 0;
    }

    return ans;
}

double log(double x)
{
    // Returns error (-1) if undefined; else, the function returns logs of values greater than 0.
    if (x <= 0)
        return -1;
    else
        return (x < 1) ? -log_hlpr(1 / x) : log_hlpr(x);
}

double ln(double x)
{
    /* Log base 10 of x all divided by log base 10 of E will yield log
    base E of x. Guaranteed to work for all values greater than 0. */
    return log(x) / log(E);
}

double exp(double x)
{
    double power = 1;
    int crnt_exp = 0;
    const double epsilon = 0.0000000000000001;

    while (x > ln(power))
    {
        power *= 2;
        crnt_exp++;
    }

    /* This algorithm zeroes in on exp(x) using ln(x) within an accuracy
    range of a predefined constant epsilon. Specifically, this algorithm
    uses powers of 2 to develop the closest posible answer within this
    range, subtracting or adding them based on the value of power. */
    while (abs(x - ln(power)) > epsilon)
    {
        crnt_exp--;

        if (ln(power) > x)
            power -= ipow(2, crnt_exp);

        else
            power += ipow(2, crnt_exp);
    }

    return power;
}

double pow(double x, double y)
{
    // Returns x^y in manner using exp() and ln() functions. Experimental.
    if (y >= 1)
        return exp(y * ln(x));
    else if (y <= -1)
        return 1 / exp(-y * ln(x));
    else if (!y)
        return 1;
    else
        return -1;
}