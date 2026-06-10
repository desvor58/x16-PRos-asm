#include <prstd.h>

u16 __prstd_alloc_curr_segment = 0x4000;
u16 __prstd_alloc_curr_offset = 0x0000;

int strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *(const u8*)str1 - *(const u8*)str2;
}

int far_strcmp(const char __far *str1, const char __far *str2)
{
    while (*str1 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *(const u8 __far*)str1 - *(const u8 __far*)str2;
}

#define _strlen_CR        \
    {                     \
        size_t len = 0;   \
        while (*str++) {  \
            len++;        \
        }                 \
        return len;       \
    }
size_t strlen(const char *str) _strlen_CR
size_t far_strlen(const char __far *str) _strlen_CR

#define _strcpy_CR        \
    {                     \
        while (*src) {    \
            *dst = *src;  \
            src++;        \
            dst++;        \
        }                 \
    }
void strcpy(char *dst, const char *src) _strcpy_CR
void far_strcpy(char __far *dst, const char __far *src) _strcpy_CR

#define _memcmp_CR                           \
    {                                        \
        for (size_t i = 0; i < size; i++) {  \
            if (*m1 != *m2) return 1;        \
            m1++;                            \
            m2++;                            \
        }                                    \
        return 0;                            \
    }
int memcmp(const char *m1, const char *m2, size_t size) _memcmp_CR
int far_memcmp(const char __far *m1, const char __far *m2, size_t size) _memcmp_CR

void *memset(void *dst, i8 val, size_t size)
{
    for (size_t i = 0; i < size; i++) *((i8*)dst++) = val;
}

void __far *far_memset(void __far *dst, i8 val, size_t size)
{
    for (size_t i = 0; i < size; i++) *((i8 __far*)dst++) = val;
}

void __far *alloc(u16 size)
{
    if ((u32)(__prstd_alloc_curr_offset + size) >= 64 * 1024U) {
        __prstd_alloc_curr_segment += 0x1000;
    }
    void __far *res = FP_MK(__prstd_alloc_curr_segment, __prstd_alloc_curr_offset);
    __prstd_alloc_curr_offset += size;
    return res;
}

void u8to_far_s_hex(u8 num, char __far *buf)
{
    static const char hex_chars[] = "0123456789ABCDEF";
    
    buf[0] = hex_chars[(num >> 4) & 0x0F];
    buf[1] = hex_chars[num & 0x0F];
    buf[2] = '\0';
}

void u16to_far_s_hex(u16 num, char __far *buf)
{
    static const char hex_chars[] = "0123456789ABCDEF";
    
    buf[0] = hex_chars[(num >> 12) & 0x0F];
    buf[1] = hex_chars[(num >> 8) & 0x0F];
    buf[2] = hex_chars[(num >> 4) & 0x0F];
    buf[3] = hex_chars[num & 0x0F];
    buf[4] = '\0';
}