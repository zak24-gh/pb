#ifndef _SYS_IO_H
#define _SYS_IO_H

#include <sys/cdefs.h>

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Writes val to port
static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ("outb %0, %1" : : "a" (val), "Nd" (port));
}

// Reads from port
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

#ifdef __cplusplus
}
#endif

#endif