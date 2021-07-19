#ifndef _STDIO_H
#define _STDIO_H
 
#include <sys/cdefs.h>
#include <kernel/mb.h>
 
#define EOF (-1)
 
#ifdef __cplusplus
extern "C" {
#endif

// printf, putchar, and puts respectively specialized for libk
int kprintf(multiboot_info_t*, const char* __restrict, ...);
int kputc(int, multiboot_info_t*);
int kputs(multiboot_info_t*, const char*);
 
#ifdef __cplusplus
}
#endif
 
#endif