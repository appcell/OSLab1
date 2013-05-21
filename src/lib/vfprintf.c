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
	for (s = format; *s; s ++) 
	{
		if(*s=='%')
		{
			s++;
			switch(*s)
			{
				case('d'):
						cnt += vfprintf(putchar_func,itoa(va_arg(ap,int),10),(va_list)NULL);
						break;
				case('x'):
						cnt += vfprintf(putchar_func,utoa(va_arg(ap,int),16),(va_list)NULL);
						break;
				case('s'):
						cnt += vfprintf(putchar_func,va_arg(ap,char *),(va_list)NULL);
						break;
				case('c'):
						cnt += vfprintf(putchar_func,va_arg(ap,char),(va_list)NULL);
						break;
				default:
						putchar_func(*s);
						cnt ++;
			}
		}
		else
		{
			putchar_func(*s);
			cnt++;
		}
	}
	return cnt;
}

