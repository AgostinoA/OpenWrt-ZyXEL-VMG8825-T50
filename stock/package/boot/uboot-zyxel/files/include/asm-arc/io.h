/******************************************************************************
 * Copyright Codito Technologies (www.codito.com) Oct 01, 2004
 * 
 * Additional contributions by ARC International, 2005.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *****************************************************************************/

/*
 *  linux/include/asm-arc/io.h
 *
 *  Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Authors : Amit Bhor
 */

#ifndef _ASM_ARC_IO_H
#define _ASM_ARC_IO_H

#define __raw_readb(addr) \
	({ unsigned int __ret; \
		__asm__ __volatile__("ldb.di %0, [%1]" : "=r"(__ret) : "r"(addr) );\
		__ret; \
	})

#define __raw_readw(addr) \
	({ unsigned int __ret; \
		__asm__ __volatile__("ldw.di %0, [%1]" : "=r"(__ret) : "r"(addr) );\
		__ret; \
	})

#define __raw_readl(addr) \
	({ unsigned int __ret; \
		__asm__ __volatile__("ld.di %0, [%1]" : "=r"(__ret) : "r"(addr) );\
		__ret; \
	})

#define __raw_writeb(b, addr) \
	__asm__ __volatile__("stb.di %0, [%1]" : : "r"(b),"r"(addr) );

#define __raw_writew(w, addr) \
	__asm__ __volatile__("stw.di %0, [%1]" : : "r"(w),"r"(addr) );

#define __raw_writel(l, addr) \
	__asm__ __volatile__("st.di %0, [%1]" : : "r"(l),"r"(addr) );

/* These can't be used, because they don't make any sense like this - PS */
#define memset_io(a,b,c)        memset((void *)(a),(b),(c))
#define memcpy_fromio(a,b,c)    memcpy((a),(void *)(b),(c))
#define memcpy_toio(a,b,c)      memcpy((void *)(a),(b),(c))

#define __io(a)                 (a)
#define __mem_pci(a)            ((unsigned long)(a))
#define __mem_isa(a)            ((unsigned long)(a))

static inline int __raw_readsb(unsigned int addr, void *data, int bytelen) {
  __asm__ __volatile__ ("1:ld.di  r8,[r0];\n"
			"sub.f  r2,r2,1;\n"
                        "bnz.d 1b;\n"
                        "stb.ab  r8,[r1,1];\n"
			: 
			: "r" (addr), "r" (data), "r" (bytelen)
			: "r8" );
  return bytelen;
}

static inline int __raw_readsw(unsigned int addr, void *data, int wordlen) {
  __asm__ __volatile__ ("1:ld.di  r8,[r0];\n"
			"sub.f  r2,r2,1;\n"
                        "bnz.d 1b;\n"
                        "stw.ab  r8,[r1,2];\n"
			: 
			: "r" (addr), "r" (data), "r" (wordlen)
			: "r8" );
  return wordlen;
}

static inline int __raw_readsl(unsigned int addr, void *data, int longlen) {
  __asm__ __volatile__ ("1:ld.di  r8,[r0];\n"
			"sub.f  r2,r2,1;\n"
                        "bnz.d 1b;\n"
                        "st.ab  r8,[r1,4];\n"
			: 
			: "r" (addr), "r" (data), "r" (longlen)
			: "r8" );
  return longlen;
}

static inline int __raw_writesb(unsigned int addr, void *data, int bytelen) {
  __asm__ __volatile__ ("1:ldb.ab  r8,[r1,1];\n"
			"sub.f  r2,r2,1;\n"
                        "bnz.d 1b;\n"
                        "st.di  r8,[r0,0];\n"
			: 
			: "r" (addr), "r" (data), "r" (bytelen)
			: "r8" );
  return bytelen;
}

static inline int __raw_writesw(unsigned int addr, void *data, int wordlen) {
   __asm__ __volatile__ ("1:ldw.ab  r8,[r1,2];\n"
			"sub.f  r2,r2,1;\n"
                        "bnz.d 1b;\n"
                        "st.ab.di  r8,[r0,0];\n"
			: 
			: "r" (addr), "r" (data), "r" (wordlen)
			: "r8" );
  return wordlen;
}

static inline int __raw_writesl(unsigned int addr, void *data, int longlen) {
  __asm__ __volatile__ ("1:ld.ab  r8,[r1,4];\n"
			"sub.f  r2,r2,1;\n"
                        "bnz.d 1b;\n"
                        "st.ab.di  r8,[r0,0];\n"
			: 
			: "r" (addr), "r" (data), "r" (longlen)
			: "r8" );
  return longlen;
}

/*
 * Generic virtual read/write
 */
#define __arch_getw(a)          __raw_getw(a)
#define __arch_putw(v,a)        __raw_putw(v,a)

#define iomem_valid_addr(iomem,sz)      (1)
#define iomem_to_phys(iomem)            (iomem)

#ifdef __io
#define outb(v,p)                       __raw_writeb(v,__io(p))
#define outw(v,p)                       __raw_writew(cpu_to_le16(v),__io(p))
#define outl(v,p)                       __raw_writel(cpu_to_le32(v),__io(p))

#define inb(p)  ({ unsigned int __v = __raw_readb(__io(p)); __v; })
#define inw(p)  ({ unsigned int __v = le16_to_cpu(__raw_readw(__io(p))); __v; })
#define inl(p)  ({ unsigned int __v = le32_to_cpu(__raw_readl(__io(p))); __v; })

#define outsb(p,d,l)                    __raw_writesb(__io(p),d,l)
#define outsw(p,d,l)                    __raw_writesw(__io(p),d,l)
#define outsl(p,d,l)                    __raw_writesl(__io(p),d,l)

#define insb(p,d,l)                     __raw_readsb(__io(p),d,l)
#define insw(p,d,l)                     __raw_readsw(__io(p),d,l)
#define insl(p,d,l)                     __raw_readsl(__io(p),d,l)
#endif

#define outb_p(val,port)                outb((val),(port))
#define outw_p(val,port)                outw((val),(port))
#define outl_p(val,port)                outl((val),(port))
#define inb_p(port)                     inb((port))
#define inw_p(port)                     inw((port))
#define inl_p(port)                     inl((port))

#define outsb_p(port,from,len)          outsb(port,from,len)
#define outsw_p(port,from,len)          outsw(port,from,len)
#define outsl_p(port,from,len)          outsl(port,from,len)
#define insb_p(port,to,len)             insb(port,to,len)
#define insw_p(port,to,len)             insw(port,to,len)
#define insl_p(port,to,len)             insl(port,to,len)

#define readb(addr) __raw_readb(addr)
#define readw(addr) __raw_readw(addr)
#define readl(addr) __raw_readl(addr)
#define writeb(b,addr) __raw_writeb(b,addr)
#define writew(w,addr) __raw_writew(w,addr)
#define writel(l,addr) __raw_writel(l,addr)

#define virt_to_phys(x) ((unsigned long)(x))
#define phys_to_virt(x) ((void*)(x))

#endif /* _ASM_ARC_IO_H */

