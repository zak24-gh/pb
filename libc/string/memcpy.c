#include <string.h>

// Copies from str2 to str1, assumes no overlap
void* memcpy(void* restrict str1, const void* restrict str2, size_t size)
{
    unsigned char* dest = (unsigned char*) str1;
    const unsigned char* src = (const unsigned char*) str2;

    for (size_t i = 0; i < size; i++)
        dest[i] = src[i];
    
    return str1;
}