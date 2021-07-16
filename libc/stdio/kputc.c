#include <stdio.h>
#include <kernel/mb.h>
#include <kernel/tty.h>

// putchar specialized for libk
int kputc(int nch, multiboot_info_t* mbi)
{
    char ch = (char) nch;
    ttywrite(&ch, sizeof(ch), mbi);

    return nch;
}