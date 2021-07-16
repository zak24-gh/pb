#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Sets bit at given index
static inline void bmset(uint32_t* bm, int index)
{
    bm[index / 0x20] |= (1 << (index % 0x20));
}

// Unsets bit at given index
static inline void bmunset(uint32_t* bm, int index)
{
    bm[index / 0x20] &= ~(1 << (index % 0x20));
}

// Tests for bit at given index
static inline int bmtest(uint32_t* bm, int index)
{
    return bm[index / 0x20] & (1 << (index % 0x20));
}

// Gets index of first unset bit
int bmfunset(uint32_t* bm, size_t size);

#ifdef __cplusplus
}
#endif

#endif