#include <string.h>

// Copies from str2 to str1, considers overlap unlike memcpy
void* memmove(void* str1, const void* str2, size_t size)
{
    unsigned char* dest = (unsigned char*) str1;
    const unsigned char* src = (const unsigned char*) str2;

    if (src > dest)
    {
        for (size_t i = 0; i < size; i++)
            dest[i] = src[i];
    }
    else
    {
        for (size_t i = size; i != 0; i--)
            dest[i - 1] = src[i - 1];
    }

    return str1;
}