#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "bitmap.h"
#include "mdeps.h"
#include <kernel/mb.h>

void minit(uint32_t map_addr, size_t size) // Memory INITialization
{
    mem_size = size;
    blocks_max = KB_TO_BLOCKS(mem_size);
    blocks_used = blocks_max;
    map = (uint32_t*) map_addr;

    map_size = blocks_max / BLOCKS_PER_DWORD;

    if (blocks_max % BLOCKS_PER_DWORD)
        map_size++;
    else {}

    memset(map, 0xFF, map_size);
}

void rginit(uint32_t base, size_t size) // ReGion INITialization
{
    size_t blocks = size / BLOCK_SIZE;
    uint32_t align = base / BLOCK_SIZE;

    for (size_t i = 0; i < blocks; i++)
    {
        bmunset(map, align++);
        blocks_used--;
    }

    bmset(map, 0);
}

void rgdeinit(uint32_t base, size_t size) // ReGion DEINITialization
{
    size_t blocks = size / BLOCK_SIZE;
    uint32_t align = base / BLOCK_SIZE;

    for (size_t i = 0; i < blocks; i++)
    {
        bmset(map, align++);
        blocks_used++;
    }
}

void rgavinit(uint32_t _memmap, uint32_t _end) // ReGions AVailable INITialization
{
    multiboot_memory_map_t* memmap = (multiboot_memory_map_t*) _memmap;
    multiboot_memory_map_t* end = (multiboot_memory_map_t*) _end;

    for (int i = 0; memmap < end; memmap++, i++)
        if (memmap -> type == MULTIBOOT_MEMORY_AVAILABLE)
            rginit((uint32_t) memmap -> addr, (size_t) memmap -> len);

}

void kldeinit(void) // KerneL DEINITialization
{
    extern uint8_t* startk;
    extern uint8_t* endk;

    size_t ksize = (size_t) &endk - (size_t) &startk;

    uint32_t map_size_align = map_size;

    if (!IS_ALIGNED(map_size_align, BLOCK_SIZE))
        map_size_align = ALIGN(map_size_align, BLOCK_SIZE);

    rgdeinit((uint32_t) &startk, ksize);
    rgdeinit((uint32_t) &endk, map_size_align);
}

void* pmalloc(void) // Physical Memory ALLOCation
{
    if (blocks_used - blocks_max <= 0)
        return NULL;
    else {}

    int index = bmfunset(map, blocks_max);

    bmset(map, index);
    blocks_used++;

    return (void*) (BLOCK_SIZE * index);
}

void pfree(void* block) // Physical FREE
{
    if (!block)
        return;

    uint32_t blockAddr = (uint32_t) block;

    int index = blockAddr / BLOCK_SIZE;
    bmunset(map, index);

    blocks_used--;
}

void fminit(multiboot_info_t* mbi) // Full Memory INITialization
{
    uint32_t actlSize = mbi -> mem_upper + 0x400;
    extern uint8_t* endk;

    minit((uint32_t) &endk, actlSize);
    rgavinit(mbi -> mmap_addr, (mbi -> mmap_addr + mbi -> mmap_length));
    kldeinit();
}