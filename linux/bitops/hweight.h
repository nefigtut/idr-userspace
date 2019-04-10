#ifndef _ASM_GENERIC_BITOPS_HWEIGHT_H_
#define _ASM_GENERIC_BITOPS_HWEIGHT_H_

#include <asm/types.h>

extern unsigned int hweight32(unsigned int w);
extern unsigned int hweight16(unsigned int w);
extern unsigned int hweight8(unsigned int w);
extern unsigned long hweight64(__u64 w);

static inline unsigned long hweight_long(unsigned long w)
{
    return sizeof(w) == 4 ? hweight32(w) : hweight64(w);
}

#endif /* _ASM_GENERIC_BITOPS_HWEIGHT_H_ */
