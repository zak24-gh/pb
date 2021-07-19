#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <sys/io.h>
#include <kernel/tty.h>
#include <kernel/psf.h>
#include <kernel/mb.h>

// tty width and height constants
static const size_t WIDTH = 1024;
static const size_t HEIGHT = 768;

// display width and height constants
static const size_t TTY_WIDTH = (size_t) WIDTH / 9;
static const size_t TTY_HEIGHT = (size_t) HEIGHT / 16;

// Declaration, but not initialization, of row, column, and color
size_t row;
size_t column;
color_t color;

// Import PSF font
extern char _binary_arch_i386_latvga_psf_start;

// Display pixel onscreen
void ttypixel(int x, int y, uint32_t color, uint8_t* fb)
{
    unsigned int loc = ((y * 4) * WIDTH) + (x * 4);
    fb[loc] = color & 0xFF;
    fb[loc + 1] = (color >> 8) & 0xFF;
    fb[loc + 2] = (color >> 16) & 0xFF;
    fb[loc + 3] = (color >> 24) & 0xFF;
}

uint32_t inpixel(int x, int y, uint8_t* fb)
{
    unsigned int loc = ((y * 4) * WIDTH) + (x * 4);
    uint32_t color = 0x000000;

    for (int i = 0; i < 4; i++)
        color += (fb[loc + i]) << (i * 8);

    return color;
}

// Clear screen
void ttycls(uint8_t* fb)
{
    for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < HEIGHT; y++)
            ttypixel(x, y, 0x000000, fb);
}

// Place PSF character
void ttyplace(unsigned short int ch, int chx, int chy, color_t color, multiboot_info_t* mbi)
{
    uint8_t* fb = (uint8_t*) (mbi -> framebuffer_addr);
    uint32_t pitch = (uint32_t) (mbi -> framebuffer_pitch);

    psf_t* font = (psf_t*) &_binary_arch_i386_latvga_psf_start;
    int bpl = ((font -> width) + 7) / 8;

    unsigned char* glyph = (unsigned char*) &_binary_arch_i386_latvga_psf_start + (font -> headersize) + ((ch > 0 && ch < (font -> numglyph) ? ch : 0) * (font -> bytesperglyph));

    int offset = (chy * (font -> height) * pitch) + (chx * ((font -> width) + 1) * sizeof(pixel_t));

    int line, mask;

    for (int y = 0; y < font -> height; y++)
    {
        line = offset;
        mask = 1 << ((font -> width) - 1);

        for (int x = 0; x < font -> width; x++)
        {
            *((pixel_t*) (fb + line)) = (*((unsigned int*) glyph) & mask) ? color.fg : color.bg;
            mask >>= 1;
            line += sizeof(pixel_t);
        }

        glyph += bpl;
        offset += pitch;
    }
}

// Initialize tty
void ttyinit(uint8_t* fb)
{
    color.fg = 0xAAAAAA;
    color.bg = 0x000000;

    row = 0;
    column = 0;

    ttycls(fb);
}

// Scroll when tty is full
void ttyscroll(uint8_t* fb)
{
    for (int y = 16; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            ttypixel(x, y - 16, inpixel(x, y, fb), fb);

    for (int lasty = HEIGHT - 16; lasty < HEIGHT; lasty++)
        for (int lastx = 0; lastx < WIDTH; lastx++)
            ttypixel(lastx, lasty, color.bg, fb);
}

// Write character to tty
void ttyputc(char ch, multiboot_info_t* mbi)
{
    ttyplace((unsigned short) ch, column, row, color, mbi);
    if (ch == '\n')
    {
        ttyplace((unsigned short) ' ', column, row, color, mbi);
        column = -1;
        row++;
    }
    else {}
    
    if (++column == TTY_WIDTH)
    {
        column = 0;
        if (++row == TTY_HEIGHT)
        {
            ttyscroll((uint8_t*) mbi -> framebuffer_addr);
            row = TTY_HEIGHT - 1;
        }
    }
    else {}

    if (row == TTY_HEIGHT)
    {
        ttyscroll((uint8_t*) mbi -> framebuffer_addr);
        row = TTY_HEIGHT - 1;
    }
}

// Write data to tty using repeated calls to ttyputc
void ttywrite(const char* data, size_t size, multiboot_info_t* mbi)
{
    for (size_t i = 0; i < size; i++)
        ttyputc(data[i], mbi);
}
