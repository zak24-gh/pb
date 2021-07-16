#ifndef MDEPS_H
#define MDEPS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Memory manager constants
#define BLOCKS_PER_DWORD    0x20
#define BLOCK_SIZE          0x1000
#define BLOCK_ALIGN         BLOCK_SIZE

// Alignment macros
#define IS_ALIGNED(address, align)  !((address) & ~((align) - 1))
#define ALIGN(address, align)       (((address) & ~((align) - 1)) + (align))

// KB to blocks conversion macro
#define KB_TO_BLOCKS(x)             (((x) / 0x400) / BLOCK_SIZE)

// Variables used in memory manager
static size_t mem_size;
static uint32_t blocks_used;
static uint32_t blocks_max;
static uint32_t* map;
static size_t map_size;

#ifdef __cplusplus
}
#endif

#endif