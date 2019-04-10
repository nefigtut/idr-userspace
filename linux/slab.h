#ifndef SLAB_H
#define SLAB_H

#include <linux/types.h>

#define SLAB_HWCACHE_ALIGN 1
#define SLAB_PANIC 2
#define SLAB_RECLAIM_ACCOUNT    0x00020000UL            /* Objects are reclaimable */

static inline int gfpflags_allow_blocking(gfp_t mask)
{
	return 1;
}

struct kmem_cache {
	int size;
	void (*ctor)(void *);
};

void *kmalloc(size_t size, gfp_t);
void kfree(void *);

static inline void *kzalloc(size_t size, gfp_t gfp)
{
	return kmalloc(size, gfp | __GFP_ZERO);
}

void *kmem_cache_alloc(struct kmem_cache *cachep, int flags);
void *kmem_cache_zalloc(struct kmem_cache *cachep, int flags);

void kmem_cache_free(struct kmem_cache *cachep, void *objp);

struct kmem_cache *
kmem_cache_create(const char *name, size_t size, size_t offset,
	unsigned long flags, void (*ctor)(void *));

#endif		/* SLAB_H */
