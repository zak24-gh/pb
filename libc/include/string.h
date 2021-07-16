#ifndef _STRING_H
#define _STRING_H
 
#include <sys/cdefs.h>
 
#include <stddef.h>
 
#ifdef __cplusplus
extern "C" {
#endif

// Performs memory comparison on two pointers
int memcmp(const void*, const void*, size_t);

// Copies from source to destination, assumes no overlap
void* memcpy(void* __restrict, const void* __restrict, size_t);

// Copies from source to destination, considers overlap
void* memmove(void*, const void*, size_t);

// Sets characters of specified pointer
void* memset(void*, int, size_t);

// Increments length to find length of string, stops at '\0'
size_t strlen(const char*);
 
#ifdef __cplusplus
}
#endif
 
#endif