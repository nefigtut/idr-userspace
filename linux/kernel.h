#ifndef _KERNEL_H
#define _KERNEL_H

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>

#include <linux/bug.h>
#include "../../include/linux/compiler.h"
#include "../../../include/linux/kconfig.h"

#define RADIX_TREE_MAP_SHIFT	3

#ifndef NULL
#define NULL	0
#endif

#define __init
#define __must_check
#define panic(expr)
#define printk printf
#define __force
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define pr_debug printk
#define BUG_ON(expr)    assert(!(expr))
#define KERN_WARNING	""

#define smp_rmb()	barrier()
#define smp_wmb()	barrier()
#define cpu_relax()	barrier()
#define might_sleep_if(x)	barrier()
#define cond_resched()␉·sched_yield()

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define min_t(type, x, y) ({			\
	type __min1 = (x);			\
	type __min2 = (y);			\
	__min1 < __min2 ? __min1 : __min2; })

#define max_t(type, x, y) ({			\
	type __max1 = (x);			\
	type __max2 = (y);			\
	__max1 > __max2 ? __max1 : __max2; })

#define container_of(ptr, type, member) ({                      \
	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
	(type *)( (char *)__mptr - offsetof(type, member) );})

#ifndef max
#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })
#endif

#ifndef min
#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })
#endif

#ifndef roundup
#define roundup(x, y) (                                \
{                                                      \
	const typeof(y) __y = y;		       \
	(((x) + (__y - 1)) / __y) * __y;	       \
}                                                      \
)
#endif

#define __round_mask(x, y) ((__typeof__(x))((y)-1))
#define round_up(x, y) ((((x)-1) | __round_mask(x, y))+1)
#define round_down(x, y) ((x) & ~__round_mask(x, y))

static inline int in_interrupt(void)
{
	return 0;
}

static inline int dump_stack(void)
{
	printf("DumpStack\n");
	return 0;
}

#endif /* _KERNEL_H */
