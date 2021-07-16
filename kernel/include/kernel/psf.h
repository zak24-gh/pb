#ifndef _KERNEL_PSF_H
#define _KERNEL_PSF_H

#include <stdint.h>

// PSF2 magic number
#define PSF_FONT_MAGIC 0x864ab572

// PSF2 info structure
typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t headersize;
    uint32_t flags;
    uint32_t numglyph;
    uint32_t bytesperglyph;
    uint32_t height;
    uint32_t width;
} psf_t;

// pixel is size of uint32_t (4 bytes)
typedef uint32_t pixel_t;

#endif