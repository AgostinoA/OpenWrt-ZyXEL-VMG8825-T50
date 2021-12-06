/* 
 * Copyright Codito Technologies (www.codito.com) 
 * 
 * Copyright (C) 
 *
 *  include/asm-arc/atomic.h
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#ifndef _ASM_ARC_ATOMIC_H
#define _ASM_ARC_ATOMIC_H

#include <linux/config.h>

#ifdef CONFIG_SMP
#error SMP not supported
#endif

typedef struct { int counter; } atomic_t;

#define ATOMIC_INIT(i)	{ (i) }

#ifdef __KERNEL__
#include <asm/system.h>

/* FIXME :: not atomic on load store architecture ? 
 * i think it wont matter. */
#define atomic_read(v)	((v)->counter)
#define atomic_set(v,i)	(((v)->counter) = (i))

static __inline__ void atomic_add(int i, volatile atomic_t *v)
{
	unsigned long flags;

	__save_flags_cli(flags);
	v->counter += i;
	__restore_flags(flags);
}

static __inline__ void atomic_sub(int i, volatile atomic_t *v)
{
	unsigned long flags;

	__save_flags_cli(flags);
	v->counter -= i;
	__restore_flags(flags);
}

static __inline__ int atomic_add_return(int i, volatile atomic_t *v)
{
	unsigned long flags ;
	long temp;

	__save_flags_cli(flags);
	v->counter += i;
	temp = v->counter;
	__restore_flags(flags);

	return temp;
}

static __inline__ int atomic_sub_return(int i, volatile atomic_t *v)
{
	unsigned long flags;
	long temp;

	__save_flags_cli(flags);
	v->counter -= i;
	temp = v->counter;
	__restore_flags(flags);

	return temp;
}

static __inline__ void atomic_inc(volatile atomic_t *v)
{
	unsigned long flags;

	__save_flags_cli(flags);
	v->counter += 1;
	__restore_flags(flags);
}

static __inline__ void atomic_dec(volatile atomic_t *v)
{
	unsigned long flags;

	__save_flags_cli(flags);
	v->counter -= 1;
	__restore_flags(flags);
}

static __inline__ int atomic_dec_and_test(volatile atomic_t *v)
{
	unsigned long flags;
	int result;

	__save_flags_cli(flags);
	v->counter -= 1;
	result = (v->counter == 0);
	__restore_flags(flags);

	return result;
}

extern __inline__ int atomic_add_negative(int i, volatile atomic_t *v)
{
	unsigned long flags;
	int result;

	__save_flags_cli(flags);
	v->counter += i;
	result = (v->counter < 0);
	__restore_flags(flags);

	return result;
}

static __inline__ void atomic_clear_mask(unsigned long mask, unsigned long *addr)
{
	unsigned long flags;

	__save_flags_cli(flags);
	*addr &= ~mask;
	__restore_flags(flags);
}

#define atomic_dec_return(v)	atomic_sub_return(1, (v))
#define atomic_inc_return(v)	atomic_add_return(1, (v))

#define smp_mb__before_atomic_dec()	barrier()
#define smp_mb__after_atomic_dec()	barrier()
#define smp_mb__before_atomic_inc()	barrier()
#define smp_mb__after_atomic_inc()	barrier()

#endif
#endif
