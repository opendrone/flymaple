/**
 * @file   misc.cpp`
 * @author tonghuix <tonghuix@tonghuix-Studio-1450>
 * @date   Fri Apr 13 18:29:54 2012
 * 
 * @brief  Misc functions and Import some standard input and output(stdio)
 * 
 * 
 */
#include <stdarg.h>
#include "misc.h"
#include "i2c.h"
#include "wirish.h"

#define BS '\b'
#define ESC 0x1B//'\e'
#define CTRL_C 0x3
#define TAB '\t'
#define SPACE ' ' 
#define ENTER '\r'
#define NEXT '\n'
#define UP  0x11
#define DOWN    0x12
#define LEFT    0x14
#define RIGHT   0x13

int putchar(char c)
{
    SerialUSB.print(c);
    return c;
}
 
int getchar(void)
{
    return SerialUSB.read();
}

 
int strlen(const char *s)
{
    const char *start = s;
 
    while (*s)
        s++;
 
    return s - start;
}
 
char *strcpy(char *s1, const char *s2)
{
    char *s = s1;
 
    while ((*s1++ = *s2++) != '\0')
        ;
 
    return s;
}
 
char *strcat( char *dst, char *src)
{
    char *s = dst + strlen(dst);
    strcpy(s, src);
 
    return dst; 
}
 
int strncmp(const char *cs, const char *ct, uint32 count)
{
    signed char __res;
    uint32 n;
 
    n = 0;
    __res = 0;
    while (n < count) {
        if ((__res = *cs - *ct++) != 0 || !*cs++)
            break;
        n++;
    }
    return __res;
}
 
int strcmp(const char *cs, const char *ct)
{
    signed char __res;
 
    while (1) {
        if ((__res = *cs - *ct++) != 0 || !*cs++)
            break;
    }
    return __res;
}

/* Not Available at this present
 *
 *
void *memcpy(void *s1, const void *s2, size_t n)
{
    char *dst = s1;
    const char *src = s2;
 
    while (n--)
        *dst++ = *src++;
 
    return s1;
}
 
void *memset(void *s1, int c, int n)
{
    char *dst = s1;
 
    while (n--)
        *dst++ = c & 0xff;
 
    return s1;
}
 
int memcmp(const void *cs, const void *ct, size_t count)
{
    const unsigned char *su1, *su2;
    int res = 0;
 
    for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
        if ((res = *su1 - *su2) != 0)
            break;
    return res;
}

***********************************************/


 
char *itox(unsigned int num)
{
    static char hex[12] = "0x";
    int i, pos;
    const char lut[]="0123456789ABCDEF";
     
    for(i = 0, pos = 2; i < 8; i++) {
        if( (hex[pos] = lut[ (num<<4*i)>>28 ]) != '0' ||  pos != 2 )
            pos++;
        hex[pos+1]='\0';
    }   
    return hex;
}

void output_int( unsigned int num, const int base )
{
    const char *digit = "0123456789ABCDEF";
    unsigned int buf[32];
    int i = 0;
    char ch;
    /*transfer the num to 10*/
    if (base == 10)
    {
        do
        {
            buf[i] = num % 10;
            num = num / 10;
            i++;
        } while ( num > 0 );
    }

    /*transfer the num to 16*/
    if (base == 16)
    {
        do
        {
            buf[i] = num % 16;
            num = num / 16;
            i++;
        } while ( num > 0 );
    }
    while ( --i >= 0 )
    {
        ch = digit[buf[i]];
        putchar( ch );
    }
}

#if 0
 
int printf(const char *format, ...)
{
    va_list unnamed_p;
	/* point to named argument */
	char *p, *sval;
	unsigned int value_i;

	/* unnamed_p point to first unnamed argument */
	va_start( unnamed_p, format);
 
    for ( p=(char *)format; *p!='\0'; p++ )
	{
		if ( *p != '%' )
		{
			putchar( *p );
			continue;
		}

		switch ( *++p )
		{
		case 'd':
			value_i = va_arg( unnamed_p, unsigned int );		
			output_int( value_i, 10 );
			break;

		case 's':
			for (sval = va_arg(unnamed_p, char*); *sval; sval++)
				putchar( *sval );
			break;

		case 'x':
			value_i = va_arg( unnamed_p, unsigned int );		
			output_int( value_i, 16 );
			break;

        case 'c':
            value_i = va_arg( unnamed_p, char );
            putchar((char)value_i);

        default:
			putchar( *p );
			break;
		}
	}
	va_end( unnamed_p );

	return 0;
}

#endif

char *puts(const char *s)
{
    char *no_standard_return =(char*) s;
    while (*s)
        putchar(*s++);
 
    return no_standard_return;
}
 
char *gets(char *s)
{
    char c;
    
    while( (c = getchar()) != ENTER)
    {
        putchar(c);
        *s++ = c;
        /*
        switch(c)
        {
            case BS:
                putchar(BS);
                break;
            case CTRL_C:
                return '\0';
            case ENTER:
                *s++ = '\0';
                return s;
            default:
                putchar(c);
                *s++ = (char)c;       
                }*/
    }
    *(s-1) = '\0';
    return s;
}

