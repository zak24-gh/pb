#ifndef _STDLIB_H
#define _STDLIB_H
 
#include <sys/cdefs.h>
#include <stddef.h>

#include <kernel/mb.h>
 
#ifdef __cplusplus
extern "C" {
#endif

// abort specialized for libk
__attribute__((__noreturn__))
void abortk(void);

// Physical Memory ALLOCation + Physical FREE
void* pmalloc(void);
void pfree(void* block);

// Full Memory INITialization
void fminit(multiboot_info_t* mbi);
 
#ifdef __cplusplus
}
#endif
 
#endif