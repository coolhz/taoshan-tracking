#ifndef __ASM_GENERIC_CMPXCHG_LOCAL_H
#define __ASM_GENERIC_CMPXCHG_LOCAL_H

#include <linux/types.h>
#include <linux/irqflags.h>

extern unsigned long wrong_size_cmpxchg(volatile void *ptr);

/*
 * Generic version of __cmpxchg_local (disables interrupts). Takes an unsigned
 * long parameter, supporting various types of architectures.
 */
static inline unsigned long __cmpxchg_local_generic(volatile void *ptr,
		unsigned long old, unsigned long new, int size)
{
	unsigned long flags, prev;

	/*
	 * Sanity checking, compile-time.
	 */
	if (size == 8 && sizeof(unsigned long) != 8)
		wrong_size_cmpxchg(ptr);

	local_irq_save(flags);
	switch (size) {
	case 1: prev = *(volatile u8 *)ptr;
		if (prev == old)
			*(volatile u8 *)ptr = (u8)new;
		break;
	case 2: prev = *(volatile u16 *)ptr;
		if (prev == old)
			*(volatile u16 *)ptr = (u16)new;
		break;
	case 4: prev = *(volatile u32 *)ptr;
		if (prev == old)
			*(volatile u32 *)ptr = (u32)new;
		break;
	case 8: prev = (unsigned long) *(volatile u64 *)ptr;
		if (prev == old)
			*(volatile u64 *)ptr = (u64)new;
		break;
	default:
		wrong_size_cmpxchg(ptr);
	}
	local_irq_restore(flags);
	return prev;
}

/*
 * Generic version of __cmpxchg64_local. Takes an u64 parameter.
 */
static inline u64 __cmpxchg64_local_generic(volatile void *ptr,
		u64 old, u64 new)
{
	u64 prev;
	unsigned long flags;

	local_irq_save(flags);
	prev = *(volatile u64 *)ptr;
	if (prev == old)
		*(volatile u64 *)ptr = new;
	local_irq_restore(flags);
	return prev;
}

#endif
