/* Code was copied from ARC GCC toolchain, ucLibc packet (GPL), memcpy.S.
/* The only changes done - access to h/w bypass cache.
 * Why memcpy-700.S was not used - it looks can load same memory address twice,
 * which is bad for me.
 */

#include "newlib_asm.h"

/*
 * void* io_copy_from(void *dest, const void *src, size_t n);
 * Access to 'src' bypass cache.
 * Function is suitable for copy data from IO-mapped device.
 * Function:
 *    - use byte,word-length operations to load/store data
 *    - use subsequent addresses when copy (do not walk back)
 *    - only load operations used for 'src'
 *    - only store operations used for 'dst'
 */
ENTRY(io_copy_from)
	
;;;  if count of copies is zero
	mov.f  lp_count,r2
	jz.d   [blink]
	or	r4,r0,r1

	and.f   0,r4,3 		;  check if 4 byte aligned
#ifndef __A4__ 
	bnz.d	@copy_bytewise_from
	lsr	r4,r2,3		;  calculate length in words
#else
	bnz.d	@copy_bytewise_from
	lsr	r4,r2
	lsr	r4,r4
	lsr	r4,r4
#endif	

	;;  Now both pointers are
	;;  4 bytes aligned.
	;;
	lsr.f	lp_count,r4
	
	sub	r1,r1,4
	sub	r3,r0,4
	lpnz	@copy16bytes_from
	ld.a.di	r4,[r1,4]
	ld.a.di	r5,[r1,4]
	ld.a.di	r6,[r1,4]
	ld.a.di	r7,[r1,4]
	st.a	r4,[r3,4]
	st.a	r5,[r3,4]
	st.a	r6,[r3,4]
	st.a	r7,[r3,4]
copy16bytes_from:		
	
	bcs.d	@remainder8bytes_from
	and.f	0,r2,4
#ifdef __A4__
	nop
#endif
	bnz.d	@copy4bytes_from
	
memcpytill1_from:
	and.f	lp_count, r2, 3
memcpy1_from:		
	add	r1,r1,3
	jz	[blink]
	add	r3,r3,3
	lp	@end_loop_from
	ldb.a.di	r4,[r1,1]
	stb.a	r4,[r3,1]
end_loop_from:	
	j	[blink]	
			
remainder8bytes_from:
	ld.a.di	r4,[r1,4]
	ld.a.di	r5,[r1,4]
	st.a	r4,[r3,4]
	bz.d	@memcpytill1_from
	st.a	r5,[r3,4]
	and.f	lp_count,r2,3
	
copy4bytes_from:	
	ld.a.di	r4,[r1,4]
	b.d	@memcpy1_from
	st.a	r4,[r3,4]

copy_bytewise_from:
	sub	r1,r1,1
	sub	r3,r0,1
	lp	@.end_bytes_from
	ldb.a.di	r4,[r1,1]
	stb.a	r4,[r3,1]
.end_bytes_from:
	j	[blink]
ENDFUNC(io_copy_from)

/*
 * void* io_copy_to(void *dest, const void *src, size_t n);
 * Similar to io_copy_from, but here access to 'dest' bypass cache.
 */
ENTRY(io_copy_to)
	
;;;  if count of copies is zero
	mov.f  lp_count,r2
	jz.d   [blink]
	or	r4,r0,r1

	and.f   0,r4,3 		;  check if 4 byte aligned
#ifndef __A4__ 
	bnz.d	@copy_bytewise_to
	lsr	r4,r2,3		;  calculate length in words
#else
	bnz.d	@copy_bytewise_to
	lsr	r4,r2
	lsr	r4,r4
	lsr	r4,r4
#endif	

	;;  Now both pointers are
	;;  4 bytes aligned.
	;;
	lsr.f	lp_count,r4
	
	sub	r1,r1,4
	sub	r3,r0,4
	lpnz	@copy16bytes_to
	ld.a	r4,[r1,4]
	ld.a	r5,[r1,4]
	ld.a	r6,[r1,4]
	ld.a	r7,[r1,4]
	st.a.di	r4,[r3,4]
	st.a.di	r5,[r3,4]
	st.a.di	r6,[r3,4]
	st.a.di	r7,[r3,4]
copy16bytes_to:		
	
	bcs.d	@remainder8bytes_to
	and.f	0,r2,4
#ifdef __A4__
	nop
#endif
	bnz.d	@copy4bytes_to
	
memcpytill1_to:
	and.f	lp_count, r2, 3
memcpy1_to:		
	add	r1,r1,3
	jz	[blink]
	add	r3,r3,3
	lp	@end_loop_to
	ldb.a	r4,[r1,1]
	stb.a.di	r4,[r3,1]
end_loop_to:	
	j	[blink]	
			
remainder8bytes_to:
	ld.a	r4,[r1,4]
	ld.a	r5,[r1,4]
	st.a.di	r4,[r3,4]
	bz.d	@memcpytill1_to
	st.a.di	r5,[r3,4]
	and.f	lp_count,r2,3
	
copy4bytes_to:	
	ld.a	r4,[r1,4]
	b.d	@memcpy1_to
	st.a.di	r4,[r3,4]

copy_bytewise_to:
	sub	r1,r1,1
	sub	r3,r0,1
	lp	@.end_bytes_to
	ldb.a	r4,[r1,1]
	stb.a.di	r4,[r3,1]
.end_bytes_to:
	j	[blink]
ENDFUNC(io_copy_to)
