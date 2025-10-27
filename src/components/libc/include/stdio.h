#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdarg.h>
#include <stddef.h>
#include "sys_uart.h"

#ifdef __cplusplus
extern "C" {
#endif
int    putchar(int c);
int    puts (const char *s);
int    printf    (const char *format, ...);
int    sprintf   (char *str, const char *format, ...);
int    snprintf  (char *str, size_t size, const char *format, ...);
int    vsprintf  (char *str, const char *format, va_list ap);
int    vsnprintf (char *str, size_t size, const char *format, va_list ap);

#ifdef __cplusplus
}
#endif

#endif
