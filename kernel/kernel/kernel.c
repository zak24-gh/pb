#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <kernel/tty.h>
#include <kernel/mb.h>

void kmain(unsigned long mb_mag, unsigned long mb_addr)
{
    // mbi is multiboot info, critical for many functions
    multiboot_info_t* mbi = (multiboot_info_t*) mb_addr;

    // Full memory initialization for memory manager
    fminit(mbi);

    // Get framebuffer for functions which require display
    uint8_t* fb = (uint8_t*) (mbi -> framebuffer_addr);

    // Initialize tty
    ttyinit(fb);

    // Default colors: fg = 0xAAAAAA, bg = 0x000000
    // Test message
    kprintf(mbi, "\"Project Bumblebee\" Version 0.0.0.6\n");
    kprintf(mbi, "\nLogin placeholder. Floats/doubles supported; further patches required for math library.\n\n");
}