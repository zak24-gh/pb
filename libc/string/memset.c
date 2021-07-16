#include <string.h>

// Sets size characters to ch in str
void* memset(void* str, int ch, size_t size)
{
    unsigned char* buffer = (unsigned char*) str;

    for (size_t i = 0; i < size; size++)
        buffer[i] = (unsigned char) ch;

    return str;
}