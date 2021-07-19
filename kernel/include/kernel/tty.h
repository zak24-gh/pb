#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

#include <kernel/mb.h>

// Color structure for PSF characters
typedef struct color {
    uint32_t fg;
    uint32_t bg;
} color_t;

// Clear screen
void ttycls(uint8_t* fb);

// Initialize tty
void ttyinit(uint8_t* fb);

// Write character to tty
void ttyputc(char ch, multiboot_info_t* mbi);

// Write data to tty using repeated calls to ttyputc
void ttywrite(const char* data, size_t size, multiboot_info_t* mbi);

// Display pixel onscreen
void ttypixel(int x, int y, uint32_t color, uint8_t* fb);

// Find color value of position
uint32_t inpixel(int x, int y, uint8_t* fb);

// Copy character from specified position to new position
void ttycopy(int srcx, int srcy, int destx, int desty, uint8_t* fb);

// Place PSF character
void ttyplace(unsigned short int ch, int chx, int chy, color_t color, multiboot_info_t* mbi);

#endif