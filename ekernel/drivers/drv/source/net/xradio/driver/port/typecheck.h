#ifndef TYPECHECK_H_INCLUDED
#define TYPECHECK_H_INCLUDED

#if defined(__CC_ARM)

#define typecheck(type,x)		1
#define typecheck_fn(type,function)	1

#elif defined(__GNUC__)

/*
 * Check at compile time that something is of a particular type.
 * Always evaluates to 1 so you may use it easily in comparisons.
 */
#define typecheck(type,x) \
({	type __dummy; \
	typeof(x) __dummy2; \
	(void)(&__dummy == &__dummy2); \
	1; \
})

/*
 * Check at compile time that 'function' is a certain type, or is a pointer
 * to that type (needs to use typedef for the function type.)
 */
#define typecheck_fn(type,function) \
({	typeof(type) __tmp = function; \
	(void)__tmp; \
})

#endif

#endif		/* TYPECHECK_H_INCLUDED */
