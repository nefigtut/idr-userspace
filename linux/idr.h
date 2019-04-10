#define RH_KABI_REPLACE2(orig, _new1, _new2)	\
	struct{ _new1; _new2;};
#define RH_KABI_DEPRECATE(_type, _orig)

#include <linux/kernel.h>
#include <linux/bitops/fls.h>
#include <linux/bitops/find.h>
#include <linux/bitops/hweight.h>
#include <linux/bitops.h>
#include <linux/bitmap.h>
#include <linux/preempt.h>
#include "../../../../include/linux/idr.h"
