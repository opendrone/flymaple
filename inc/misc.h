/**
 * @file   misc.h
 * @author tonghuix <tonghuix@tonghuix-Studio-1450>
 * @date   Fri Apr 13 18:31:11 2012
 * 
 * @brief  Misc functions header definiation
 * 
 * 
 */

#ifndef __MISC_H__
#define __MISC_H__

#include "libmaple_types.h"

void writeTo(uint8 DEVICE, uint8 address, uint8 val);

void readFrom(uint8 DEVICE, uint8 address, uint8 num, uint8 *msg_data);

 
int strlen(const char *s);

char *strcpy(char *s1, const char *s2);

char *strcat( char *dst, char *src);

int strncmp(const char *cs, const char *ct, uint32 count);

int strcmp(const char *cs, const char *ct);

/* Not Available at this present
 *
 *
void *memcpy(void *s1, const void *s2, size_t n);

void *memset(void *s1, int c, int n);

int memcmp(const void *cs, const void *ct, size_t count);

***********************************************/


unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base);

char *itox(unsigned int num);

int printf(const char *format, ...);

char *puts(const char *s);

char *gets(char *s);

int putchar(char c);

int getchar(void);

#endif
