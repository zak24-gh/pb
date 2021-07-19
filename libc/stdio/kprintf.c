#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <kernel/mb.h>

// Used to print characters and return false if EOF is found
static bool print(const char* data, size_t size, multiboot_info_t* mbi)
{
    const unsigned char* bytes = (const unsigned char*) data;
    for (size_t i = 0; i < size; i++)
        if (kputc(bytes[i], mbi) == EOF)
            return false;
    return true;
}

// printf specialized for libk
int kprintf(multiboot_info_t* mbi, const char* restrict format, ...)
{
    va_list args;
    va_start(args, format);

    int written = 0;

    while (*format)
    {
        size_t max_chars = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%')
        {
            if (format[0] == '%')
                format++;

            size_t amount = 1;

            while (format[amount] && format[amount] != '%')
                amount++;
            
            if (amount > max_chars)
            {
                // overflow
                return -1;
            }

            if (!print(format, amount, mbi))
                return -1;

            format += amount;
            written += amount;
            continue;
        }
        else {}

        const char* fmt_start = format++;

        if (*format == 'c')
        {
            format++;
            char ch = (char) va_arg(args, int);

            if (!max_chars)
            {
                // Overflow
                return -1;
            }
            else {}

            if (!print(&ch, sizeof(ch), mbi))
                return -1;
            else {}

            written++;
        }
        else if (*format == 's')
        {
            format++;
            const char* str = va_arg(args, const char*);

            size_t length = strlen(str);

            if (length > max_chars)
            {
                // Overflow
                return -1;
            }
            else {}

            if (!print(str, length, mbi))
                return -1;

            written += length;
        }
        else
        {
            format = fmt_start;

            size_t length = strlen(format);

            if (length > max_chars)
            {
                // Overflow
                return -1;
            }
            else {}

            if (!print(format, length, mbi))
                return -1;
            else {}

            written += length;
            format += length;
        }
    }    

    va_end(args);
    return written;
}