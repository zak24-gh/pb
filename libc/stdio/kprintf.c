#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <kernel/mb.h>
#include <kernel/tty.h>

const char* hex_lower = "0123456789abcdef";
const char* hex_upper = "0123456789ABCDEF";
const char* dec = "0123456789";

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

            if (!print(&ch, sizeof(ch), mbi))
                return -1;
            
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
            
            if (!print(str, length, mbi))
                return -1;

            written += length;
        }
        else if ((*format == 'x') || (*format == 'X'))
        {
            bool upper = (*format == 'X');

            format++;
            unsigned int value = va_arg(args, unsigned int);

            char buf[32] = {[31] = 0};
            int i = 30;

            if (value)
            {
                if (upper)
                    for (; value && i; i--, value /= 16)
                        buf[i] = hex_upper[value % 16];
                else
                    for (; value && i; i--, value /= 16)
                        buf[i] = hex_lower[value % 16];
            }
            else
            {
                buf[i] = '0';
                i--;
            }
            
            char* intstr = &buf[i + 1];
            size_t length = strlen(intstr);

            if (length > max_chars)
            {
                // Overflow
                return -1;
            }
            
            if (!print(intstr, length, mbi))
                return -1;
            
            written += length;
        }
        else if (*format == 'f')
        {
            format++;
            double flvalue = va_arg(args, double);
            int64_t value = abs(flvalue) * (double) ipow(10, 8);
            bool isneg = (flvalue < 0);
            int ratio = (int) (ipow(10, 8) / value);
            int offset = 0;

            if (ratio > 1)
                while (ratio)
                {
                    offset++;
                    ratio /= 10;
                }

            offset--;
            char buf[32] = {[31] = 0};
            int i = 30;
            
            if (value)
            {
                for (; value && i; i--, value /= 10)
                {
                    if (i == 22)
                    {
                        buf[i] = '.';
                        i--;
                        break;
                    }
                    buf[i] = dec[value % 10];
                }
                for (; value && i; i--, value /= 10)
                    buf[i] = dec[value % 10];
                if (((0 < flvalue) && (flvalue < 1)) || ((0 > flvalue) && (flvalue > -1)))
                {
                    memmove(&buf[21], "0.", 2);
                    i -= 2;
                    if ((flvalue < 0.1) && (-0.1 < flvalue))
                        while (offset)
                        {
                            buf[22 + offset] = '0';
                            offset--;
                            i--;
                        }
                }
            }
            else
            {
                memmove(&buf[21], "0.00000000", 10);
                i = 20;
            }
            
            if (isneg)
            {
                buf[i] = '-';
                i--;
            }
            
            char* intstr = &buf[i + 1];
            size_t length = strlen(intstr);

            if (length > max_chars)
            {
                // Overflow
                return -1;
            }
            
            if (!print(intstr, length, mbi))
                return -1;
            
            written += length;
        }
        else if (*format == 'd')
        {
            format++;
            int value = va_arg(args, int);
            char buf[32] = {[31] = 0};
            int i = 30;
            bool isneg = (value < 0);

            if (isneg)
                value = -value;
            
            if (value)
            {
                for (; value && i; i--, value /= 10)
                    buf[i] = dec[value % 10];
            }
            else
            {
                buf[i] = '0';
                i--;
            }
            
            if (isneg)
            {
                buf[i] = '-';
                i--;
            }
            
            char* intstr = &buf[i + 1];
            size_t length = strlen(intstr);

            if (length > max_chars)
            {
                // Overflow
                return -1;
            }
            
            if (!print(intstr, length, mbi))
                return -1;
            
            written += length;
        }
        else if ((*format == 'u') || (*format == 'i'))
        {
            format++;
            unsigned int value = va_arg(args, unsigned int);

            char buf[32] = {[31] = 0};
            int i = 30;

            if (value)
            {
                for (; value && i; i--, value /= 10)
                    buf[i] = dec[value % 10];
            }
            else
            {
                buf[i] = '0';
                i--;
            }
            
            char* intstr = &buf[i + 1];
            size_t length = strlen(intstr);

            if (length > max_chars)
            {
                // Overflow
                return -1;
            }
            
            if (!print(intstr, length, mbi))
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

            if (!print(format, length, mbi))
                return -1;
            
            written += length;
            format += length;
        }
    }    

    va_end(args);
    return written;
}