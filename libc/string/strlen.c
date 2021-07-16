#include <string.h>

// Increments length to find length of string, stops at '\0'
size_t strlen(const char* str)
{
    size_t length = 0;
    while (str[length])
        length++;
    return length;
}