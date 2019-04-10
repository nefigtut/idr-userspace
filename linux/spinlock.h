#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <linux/types.h>

#define SPINLOCK_INITIALIZER { 0 }
#define DEFINE_SPINLOCK(z)	spinlock_t z = SPINLOCK_INITIALIZER

#define spin_lock_init(z)		(z)->x = 0
#define spin_lock_irqsave(z, f)		(void)f, (z)->x = 1
#define spin_unlock_irqrestore(z, f)	(void)f, (z)->x = 0

#endif		/* SPINLOCK_H */
