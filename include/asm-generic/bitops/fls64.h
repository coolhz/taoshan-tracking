#ifndef _ASM_GENERIC_BITOPS_FLS64_H_
#define _ASM_GENERIC_BITOPS_FLS64_H_

#include <asm/types.h>

/**
 * fls64 - find last set bit in a 64-bit word
 * @x: the word to search
 *
 * This is defined in a similar way as the libc and compiler builtin
 * ffsll, but returns the position of the most significant set bit.
 *
 * fls64(value) returns 0 if value is 0 or the position of the last
 * set bit if value is nonzero. The last (most significant) bit is
 * at position 64.
 */
#if BITS_PER_LONG == 32
static __always_inline int fls64(__u64 x)
{
	__u32 h = (__u32) (x >> 32);
	if (h)
		return fls((int)h) + 32;
	return fls((int)x);
}
#elif BITS_PER_LONG == 64
static __always_inline int fls64(__u64 x)
{
	if (x == 0)
		return 0;
	return __fls((int)x) + 1;
}
#else
#error BITS_PER_LONG not 32 or 64
#endif

#endif /* _ASM_GENERIC_BITOPS_FLS64_H_ */
