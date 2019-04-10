#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <assert.h>

#include <linux/mempool.h>
#include <linux/slab.h>
#include <urcu/uatomic.h>

int nr_allocated = 0, sz_allocated = 0, ma_allocated = 0;

void *mempool_alloc(mempool_t *pool, int gfp_mask)
{
	return pool->alloc(gfp_mask, pool->data);
}

void mempool_free(void *element, mempool_t *pool)
{
	pool->free(element, pool->data);
}

mempool_t *mempool_create(int min_nr, mempool_alloc_t *alloc_fn,
			mempool_free_t *free_fn, void *pool_data)
{
	mempool_t *ret = malloc(sizeof(*ret));

	ret->alloc = alloc_fn;
	ret->free = free_fn;
	ret->data = pool_data;
	return ret;
}

void *kmem_cache_alloc(struct kmem_cache *cachep, int flags)
{
	void *ret = malloc(cachep->size);
	if (cachep->ctor)
		cachep->ctor(ret);
	uatomic_inc(&nr_allocated);
	uatomic_add(&sz_allocated, cachep->size);

	printf("kmem_cache_alloc: %p lvl %d\n", ret, *((int*)ret+523));
	return ret;
}

void *kmem_cache_zalloc(struct kmem_cache *cachep, int flags)
{
	void *ret = kmem_cache_alloc(cachep, flags);
	if (ret)
		memset(ret, 0, cachep->size);
	return ret;
}

void kmem_cache_free(struct kmem_cache *cachep, void *objp)
{
	assert(objp);
	uatomic_dec(&nr_allocated);
	uatomic_sub(&sz_allocated, cachep->size);

	printf("kmem_cache_free: %p lvl %d\n", objp, *((int*)objp+523));
	memset(objp, 0, cachep->size);
	free(objp);
}

void *kmalloc(size_t size, gfp_t gfp)
{
	void *ret;

	ret = malloc(size);
	if (!ret)
		return ret;

	uatomic_inc(&nr_allocated);
	uatomic_add(&ma_allocated, size);

	if (gfp & __GFP_ZERO)
		memset(ret, 0, size);

	printf("kmalloc: %p sz %ld\n", ret, size);
	return ret;
}

void kfree(void *p)
{
	if (!p)
		return;
	uatomic_dec(&nr_allocated);
	uatomic_sub(&ma_allocated, malloc_usable_size(p));

	printf("kfree: %p sz %ld\n", p, malloc_usable_size(p));
	free(p);
}

struct kmem_cache *
kmem_cache_create(const char *name, size_t size, size_t offset,
	unsigned long flags, void (*ctor)(void *))
{
	struct kmem_cache *ret;

	printf("kmem_cache_create: name %s size %ld undersz %ld\n", name, size, sizeof(*ret));
	ret = malloc(sizeof(*ret));
	if (!ret)
		return ret;

	printf("allocated\n");
	ret->size = size;
	ret->ctor = ctor;
	return ret;
}
