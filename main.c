#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>

#include <linux/slab.h>
#include <linux/idr.h>

extern int nr_allocated, sz_allocated, ma_allocated;

struct idr tidr;

void idr_layer_print(struct idr_layer *p, int level, int high)
{
    int i;

    for(i=0; i<level; i++)
	printf("  ");
    if (p) printf("%p:%d: ", p, p->layer);
	else { printf("NULL\n"); return; };

    for(i=0; i<(1<<IDR_BITS); i++)
	if (p->ary[i]) {
	    printf("%d:%p ", i, p->ary[i]);
	    if (p->layer == 0)
		printf("(%d) ", (high<<IDR_BITS)+i);
	}
    printf("\n");

    if (p->layer == 0) return;

    for(i=0; i<(1<<IDR_BITS); i++)
        if (p->ary[i])
            idr_layer_print(p->ary[i], level + 1, (high<<IDR_BITS)+i );
}

int main(int argc, char **argv)
{
	int id;
	void *ptr;

/*
	bool long_run = false;
	int opt;

	while ((opt = getopt(argc, argv, "l")) != -1) {
		if (opt == 'l')
			long_run = true;
	}
*/

	rcu_register_thread();

	idr_init_cache();
	idr_init(&tidr);
	printf("initilized\n");

    idr_preload(GFP_KERNEL);
    //id = idr_alloc(&tidr, (void*)3, 17741824, 17741824+4000, GFP_NOWAIT);
    //id = idr_alloc(&tidr, (void*)2, 4194305, 4194305+4000, GFP_NOWAIT);
    //id = idr_alloc(&tidr, (void*)1, 173073, 173073+4000, GFP_NOWAIT);
    //id = idr_alloc(&tidr, (void*)4, 1073741824, 1073741824+4000, GFP_NOWAIT);
    id = idr_alloc(&tidr, (void*)5, 1073741824, 1073741824, GFP_NOWAIT);
    id = idr_alloc(&tidr, (void*)5, 2147483647, 2147483647, GFP_NOWAIT);
    idr_preload_end();


    printf("idr_for_each:\n");
    idr_for_each_entry(&tidr, ptr, id) {
        printf("    ptr %p id %d %x\n", ptr, id, id); }

	printf("tidr: layers %d id_free_cnt %d\n", tidr.layers, tidr.id_free_cnt);

	idr_layer_print(tidr.top, 0, 0);

	//idr_remove(&tidr, 173073);
	//idr_remove(&tidr, 4194305);
	//idr_remove(&tidr, 17741824);
	//idr_remove(&tidr, 1073741824);
	//idr_remove(&tidr, 1073741825);
	//idr_layer_print(tidr.top, 0);
	usleep(200*1000);

	printf("idr_remove_all:\n");
	__idr_remove_all(&tidr);
	usleep(200*1000);

	printf("idr_destroy:\n");
	idr_destroy(&tidr);

	usleep(200*1000);
	rcu_unregister_thread();
	printf("after sleep(1): num %d size %d malloc %d \n", nr_allocated, sz_allocated, ma_allocated);
	exit(0);
}

/*
struct idr_layer {
␉···int␉␉···␉···prefix;␉// the ID prefix of this idr_layer
␉···DECLARE_BITMAP(bitmap, IDR_SIZE); // A zero bit means "space here"
␉···struct idr_layer __rcu␉·*ary[1<<IDR_BITS];
␉···int␉␉···␉···count;␉·// When zero, we can release it
␉···int␉␉···␉···layer;␉·// distance from leaf
␉···struct rcu_head␉␉···rcu_head;
};

struct idr {
␉···struct idr_layer __rcu␉·*hint;␉·// the last layer allocated from
␉···struct idr_layer __rcu␉·*top;
␉···struct idr_layer␉···*id_free;
␉···int␉␉···␉···layers;␉// only valid w/o concurrent changes
␉···int␉␉···␉···id_free_cnt;
␉···int␉␉···␉···cur;␉···// current pos for cyclic allocation
␉···spinlock_t␉·␉···lock;
};
*/
