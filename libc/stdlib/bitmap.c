#include <stdint.h>
#include <stddef.h>
#include <limits.h>

#include "bitmap.h"

// Gets index of first unset bit
int bmfunset(uint32_t* bm, size_t size)
{
    uint32_t rem_bits = size % 0x20;

    for (uint32_t i = 0; i < (size / 0x20); i++)
        if (bm[i] != UINT32_MAX)
            for (int j = 0; j < 0x20; j++)
                if (!(bm[i] & (1 << j)))
                    return (i * 0x20) + j;

    if (rem_bits)
    {
        for (uint32_t k = 0; k < rem_bits; k++)
            if (!(bm[size / 0x20] & (1 << k)))
                return size + k;
    }
    else {}

    return -1;
}