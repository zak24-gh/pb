#include <stdint.h>
#include <limits.h>
#include <math.h>

#define E (2.7182818284590452)
#define PI (3.1415936535897932)

double ipow_hlpr(double x, uint64_t y)
{
    double power = 1;
    
    for (int i = 0; i < y; i++)
        power *= x;
        
    return power;
}

double ipow(double x, int64_t y)
{
    double power = 0;

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
    
    for (uint8_t i = 1; i <= x; i++)
        _fact *= i;
        
    return _fact;
}

double nrt(double x, double n)
{
	double _nrt = 0;
	double current = 1;
	double epsilon = 0.0000000000000001;
    double diff = INT_MAX;
    double prev = 1;

	if (x < 0)
		return -1;

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
	return nrt(x, 2);
}

double log_hlpr(double x)
{
    double current = x;
    double temp = current;
    double ans = 0;
    uint8_t digit = 0;

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
    if (x <= 0)
        return -1;
    else
        return (x < 1) ? -log_hlpr(1 / x) : log_hlpr(x);
}

double ln(double x)
{
    return log(x) / log(E);
}

double exp(double x)
{
    double power = 1;
    int crnt_exp = 0;
    double epsilon = 0.0000000000000001;

    while (x > ln(power))
    {
        power *= 2;
        crnt_exp++;
    }

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
    return exp(y * ln(x));
}