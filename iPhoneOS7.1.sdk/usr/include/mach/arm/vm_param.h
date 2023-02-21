/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
 */
/*
 * FILE_ID: vm_param.h
 */

/*
 *	ARM machine dependent virtual memory parameters.
 */

#ifndef	_MACH_ARM_VM_PARAM_H_
#define _MACH_ARM_VM_PARAM_H_

#define BYTE_SIZE	8	/* byte size in bits */

#define ARM_PGBYTES	4096	/* bytes per ARM small page */
#define ARM_PGSHIFT	12	/* number of bits to shift for pages */


#if defined (KERNEL) || !defined (__arm64__)

#define PAGE_SIZE       ARM_PGBYTES
#define PAGE_SHIFT     ARM_PGSHIFT
#define PAGE_MASK      (PAGE_SIZE-1)
#define VM_PAGE_SIZE	ARM_PGBYTES
#define	machine_ptob(x)	((x) << ARM_PGSHIFT)

#else

/* ARM64 userland gets a 16k pagesize */
#define PAGE_SIZE    	(0x4000)
#define PAGE_SHIFT    	(14)
#define PAGE_MASK      (PAGE_SIZE-1)

#define VM_PAGE_SIZE	PAGE_SIZE

#define	machine_ptob(x)	((x) << 14)

#endif

#if defined(__arm64__)
#define KERNEL_STACK_SIZE	(5*ARM_PGBYTES)
#else
#define KERNEL_STACK_SIZE	(4*ARM_PGBYTES)
#endif
#define INTSTACK_SIZE		(4*ARM_PGBYTES)
						/* interrupt stack size */

#ifndef __ASSEMBLER__
/*
 *	Round off or truncate to the nearest page.  These will work
 *	for either addresses or counts.  (i.e. 1 byte rounds to 1 page
 *	bytes.
 */


#if defined (__arm__)

#define VM_MIN_ADDRESS		((vm_address_t) 0x00000000)
#define VM_MAX_ADDRESS		((vm_address_t) 0x80000000)

#define HIGH_EXC_VECTORS	((vm_address_t) 0xFFFF0000)

#define VM_MIN_KERNEL_ADDRESS	((vm_address_t) 0x80000000)
#define VM_MIN_KERNEL_AND_KEXT_ADDRESS VM_MIN_KERNEL_ADDRESS
#define VM_HIGH_KERNEL_WINDOW	((vm_address_t) 0xFFFE0000)
#define VM_MAX_KERNEL_ADDRESS	((vm_address_t) 0xFFFEFFFF)

#define VM_KERNEL_ADDRESS(va)	((((vm_address_t)(va))>=VM_MIN_KERNEL_ADDRESS) && \
              (((vm_address_t)(va))<=VM_MAX_KERNEL_ADDRESS))

/* system-wide values */
#define MACH_VM_MIN_ADDRESS		((mach_vm_offset_t) 0)
#define MACH_VM_MAX_ADDRESS		((mach_vm_offset_t) VM_MAX_ADDRESS)

#elif defined (__arm64__)

#define VM_MIN_ADDRESS		((vm_address_t) 0x0000000000000000ULL)
#define VM_MAX_ADDRESS		((vm_address_t) 0x0000000080000000ULL)

#define VM_MIN_KERNEL_ADDRESS	((vm_address_t) 0xffffff8000000000ULL)
#define VM_MIN_KERNEL_AND_KEXT_ADDRESS VM_MIN_KERNEL_ADDRESS
#define VM_MAX_KERNEL_ADDRESS	((vm_address_t) 0xffffff80ffffffffULL)

#define VM_KERNEL_ADDRESS(va)	((((vm_address_t)(va))>=VM_MIN_KERNEL_ADDRESS) && \
              (((vm_address_t)(va))<=VM_MAX_KERNEL_ADDRESS))

/* system-wide values */
#define MACH_VM_MIN_ADDRESS		((mach_vm_offset_t) 0x0ULL)
#define MACH_VM_MAX_ADDRESS		((mach_vm_offset_t) 0x00000001A0000000ULL)

#else
#error architecture not supported
#endif

/*
 *	Physical memory is mapped linearly at an offset virtual memory.
 */
extern unsigned long gVirtBase, gPhysBase, gPhysSize;
#define isphysmem(a) (((vm_address_t)(a) - gPhysBase) < gPhysSize)
#define phystokv(a)	((vm_address_t)(a) - gPhysBase + gVirtBase)
#endif

#define SWI_SYSCALL	0x80

#endif	/* _MACH_ARM_VM_PARAM_H_ */

