#include <stdio.h>

#include <kernel/mb.h>

// puts specialized for libk
int kputs(multiboot_info_t* mbi, const char* str)
{
    return kprintf(mbi, "%s\n", str);
}