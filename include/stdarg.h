#ifdef _M_ALPHA
typedef struct {
char *a0; /* pointer to first homed integer argument */
int offset; /* byte offset of next parameter */
} va_list;
#else
typedef char * va_list;
#endif

#define _INTSIZEOF(n) ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
#define va_start(ap,v) ( ap = (va_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap) ( ap = (va_list)0 )
