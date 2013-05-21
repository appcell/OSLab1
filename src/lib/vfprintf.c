#include "string.h"
#include "assert.h"
#include "common.h"
#include "stdarg.h"
/*
 * use putchar_func to print a string
 *   @putchar_func is a function pointer to print a character
 *   @format is the control format string (e.g. "%d + %d = %d")
 *   @data is the address of the first variable argument
 * please implement it.
 */
int
vfprintf(void (*putchar_func)(char), const char *format, va_list ap) {
	const char *s;
	int cnt = 0;
	for (s = format; *s; s ++) {
		if(*s='%')
		{
			s++;
			switch(*s)
			{
				case('d'):
					{
						cnt += vfprintf(putchar_func,itoa(),ap)

					}
			}
		}
		putchar_func(*s);
	}
	return 0;
}

