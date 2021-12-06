/* Copyright (C) 2007 ARC International (UK) LTD */

/* Code was copied from ARC GCC toolchain, ucLibc packet (GPL) */

#include "newlib_asm.h"

#ifndef __A4__

#define SMALL	7 /* Must be at least 6 to deal with alignment/loop issues.  */

ENTRY(memset)
#ifndef	__ARC700__
#undef SMALL
#define SMALL 8 /* Even faster if aligned.  */
	brls.d	r2,SMALL,.Ltiny
#endif
	mov_s	r4,r0
	or	r12,r0,r2
	bmsk.f	r12,r12,1
	extb_s	r1,r1
	asl	r3,r1,8
	beq.d	.Laligned
	or_s	r1,r1,r3
#ifdef __ARC700__
	brls	r2,SMALL,.Ltiny
#endif
	add	r3,r2,r0
	stb	r1,[r3,-1]
	bclr_s	r3,r3,0
	stw	r1,[r3,-2]
	bmsk.f	r12,r0,1
	add_s	r2,r2,r12
	sub.ne	r2,r2,4
	stb.ab	r1,[r4,1]
	and	r4,r4,-2
	stw.ab	r1,[r4,2]
	and	r4,r4,-4
.Laligned:	; This code address should be aligned for speed.
#ifdef __ARC700__
	asl	r3,r1,16
	lsr.f	lp_count,r2,2
	or_s	r1,r1,r3
	lpne	.Loop_end
	st.ab	r1,[r4,4]
.Loop_end:
	j_s	[blink]
#else /* !__ARC700 */
	lsr.f	lp_count,r2,3
	asl	r3,r1,16
	or_s	r1,r1,r3
	lpne	.Loop_end
	st.ab	r1,[r4,4]
	st.ab	r1,[r4,4]
.Loop_end:
	sub.cc	r4,r4,4
	j_s.d	[blink]
	st	r1,[r4]
#endif /* !__ARC700 */

#ifdef __ARC700__
	.balign	4
.Ltiny:
	mov.f	lp_count,r2
	lpne	.Ltiny_end
	stb.ab	r1,[r4,1]
.Ltiny_end:
	j_s	[blink]
#else /* !__ARC700__ */
#if SMALL > 8
FIXME
#endif
	.balign	4
	stb_s	r1,[r0,7]
	stb_s	r1,[r0,6]
	stb_s	r1,[r0,5]
	stb_s	r1,[r0,4]
	stb_s	r1,[r0,3]
	stb_s	r1,[r0,2]
	stb_s	r1,[r0,1]
	stb_s	r1,[r0]
	.endr
	j_s	[blink]
.Ltiny:	; must be misaligned - so that we hit the j_s [blink] for zero bytes!
	sub1	r3,pcl,r2
	j_s	[r3]
#endif /* !__ARC700 */
ENDFUNC(memset)
#endif /* !__A4__ */
