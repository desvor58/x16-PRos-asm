#ifndef __PRSTD_H__
#define __PRSTD_H__

typedef          char i8;
typedef unsigned char u8;
typedef          int  i16;
typedef unsigned int  u16;
typedef          long i32;
typedef unsigned long u32;
typedef           u32 size_t;

#define FP_MK(seg, off) ((void __far*)(((u32)(seg) << 16) | (u16)(off)))
#define FP_SEG(fp) (((u32)(fp) >> 16) & 0xFFFF)
#define FP_OFF(fp) ((u16)(fp) & 0xFFFF)

#define is_space(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')
#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define is_alpha(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))

extern char *args;

extern u16 __prstd_alloc_curr_segment;
extern u16 __prstd_alloc_curr_offset;

/*************************************************************
 * put char
 * ch - char to put
 *************************************************************/
void putchar(const char ch);

/*************************************************************
 * put null terminated str with \n at end
 * str - pointer to null terminated string in DS segment
 *************************************************************/
void puts(const char *str);

/*************************************************************
 * put null terminated str in specified segment with \n at end
 * seg - segment of str
 * offset - offset in segment to str
 * (work at BIOS interupts)
 *************************************************************/
void far_puts(const char __far *str);

/*************************************************************
 * put null terminated str without \n at end
 * str - pointer to null terminated string in DS segment
 *************************************************************/
void prints(const char *str);

/*************************************************************
 * put null terminated __far str without \n at end
 * str - __far pointer to null terminated string
 *************************************************************/
void far_prints(const char __far *str);

/*************************************************************
 * reading file witch size < 32KiB
 * buf - buffer to write file text
 * filename - file name string
 * return - size of readd text (if error returns -1)
 *************************************************************/
int load_file(char *buf, const char *filename);

/*************************************************************
 * reading file witch size > 32KiB
 * seg - segment to write file test
 * offset - offset in seg to write
 * filename - file name string IN SEG!
 * return - 1 if error, else returns 0
 *************************************************************/
int load_huge_file(u16 seg, u16 offset, const char *filename);

/*************************************************************
 * write buffer to file
 * buf - __far pointer to buffer for writing
 * size - size of text to write
 * filename - name of file for writing
 * return - 1 if error, else returns 0
 *************************************************************/
/* int write_file(u16 seg, u16 buf_offset, u16 size, u16 filename_offset); */

/*************************************************************
 * compare 2 strings
 * str1, str2 - strings to compare
 * return - 0 if equals, else returns !0
 *************************************************************/
int strcmp(const char *str1, const char *str2);

/*************************************************************
 * compare 2 __far strings
 * str1, str2 - __far strings to compare
 * return - 0 if equals, else returns !0
 *************************************************************/
int far_strcmp(const char __far *str1, const char __far *str2);

/*************************************************************
 * calculate str length
 * str - string to calculate
 * return - length of string without '\0'
 *************************************************************/
size_t strlen(const char *str);

/*************************************************************
 * calculate __far str length
 * str - string to calculate
 * return - length of string without '\0'
 *************************************************************/
size_t far_strlen(const char __far *str);

/*************************************************************
 * copy text from src string to dst string with \0
 * dst - destination string
 * src - source string
 *************************************************************/
void strcpy(char *dst, const char *src);

/*************************************************************
 * copy text from src __far string to dst __far string with \0
 * dst - destination string
 * src - source string
 *************************************************************/
void far_strcpy(char __far *dst, const char __far *src);

/*************************************************************
 * compare 2 mem buffer with size
 * m1, m2 - mem buf to compare
 * size - size of buffers
 * return - 0 if equals, else returns 1
 *************************************************************/
int memcmp(const char *m1, const char *m2, size_t size);

/*************************************************************
 * compare 2 __far mem buffer with size
 * str1, str2 - strings to compare
 * size - size of buffers
 * return - 0 if equals, else returns 1
 *************************************************************/
int far_memcmp(const char __far *m1, const char __far *m2, size_t size);

/*************************************************************
 * set first *size bytes in dst buf to val
 * dst - destination buf
 * val - value to set
 * size - count bytes to set in dst
 * return - dst
 *************************************************************/
void *memset(void *dst, i8 val, size_t size);

/*************************************************************
 * set first *size bytes in __far dst buf to val
 * dst - destination buf
 * val - value to set
 * size - count bytes to set in dst
 * return - dst
 *************************************************************/
void __far *far_memset(void __far *dst, i8 val, size_t size);

/*************************************************************
 * copy *size bytes from *dst to *src
 * dst - pointer to destination buf
 * src - pointer to source buf
 * size - count bytes to copy
 * return - dst
 *************************************************************/
void *memcpy(void *dst, void *src, u16 size);

/*************************************************************
 * copy *size bytes from *dst to *src
 * dst - __far pointer to destination buf
 * src - __far pointer to source buf
 * size - count bytes to copy
 * return - dst
 *************************************************************/
void __far *far_memcpy(void __far *dst, void __far *src, u16 size);

/*************************************************************
 * check if str is digit
 * str - string to check
 * return:
 *   0 - str is not digit
 *   1 - str is decimal
 *   2 - str is hex
 *   3 - str is bin
 *************************************************************/
int sisd(const char *str);

/*************************************************************
 * num -> str
 *************************************************************/
void u8to_far_s(u8 num, char __far *buf);

/*************************************************************
 * num -> str  as hex
 *************************************************************/
void u8to_far_s_hex(u8 num, char __far *buf);

void u16to_far_s_hex(u16 num, char __far *buf);

void __far *alloc(u16 size);

#endif