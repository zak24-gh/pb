#include <string.h>

// Performs memory comparison on two pointers
int memcmp(const void* str1, const void* str2, size_t size)
{
    const unsigned char* a = (const unsigned char*) str1;
    const unsigned char* b = (const unsigned char*) str2;
    for (size_t i = 0; i < size; i++)
    {
        if (a[i] > b[i])
            return 1;
        else if (a[i] < b[i])
            return -1;
    }
    return 0;
}