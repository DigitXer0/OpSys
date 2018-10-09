
#ifndef _STDARG_H_
#define _STDARG_H_

#ifndef	_VA_LIST
#define _VA_LIST
typedef __builtin_va_list va_list;

typedef char* va_list;
#endif

#define __va_argsiz(t)	\
	(((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))


#ifdef	__GNUC__
#define va_start(ap, pN)	\
	((ap) = ((va_list) __builtin_next_arg(pN)))
#else

#define va_start(ap, pN)	\
	((ap) = ((va_list) (&pN) + __va_argsiz(pN)))
#endif

#define va_end(ap)	((void)0)

#define va_arg(ap, t)					\
	 (((ap) = (ap) + __va_argsiz(t)),		\
	  *((t*) (void*) ((ap) - __va_argsiz(t))))

#endif