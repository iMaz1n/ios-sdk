/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 */
/*
 * @OSF_COPYRIGHT@
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 */

/*
 *	File:	vm_types.h
 *	Author:	Avadis Tevanian, Jr.
 *	Date: 1985
 *
 *	Header file for VM data types.  ARM version.
 */

#ifndef	_MACH_ARM_VM_TYPES_H_
#define _MACH_ARM_VM_TYPES_H_

#ifndef	ASSEMBLER

#include <arm/_types.h>
#include <mach/arm/vm_param.h>
#include <stdint.h>
#include <Availability.h>

/*
 * natural_t and integer_t are Mach's legacy types for machine-
 * independent integer types (unsigned, and signed, respectively).
 * Their original purpose was to define other types in a machine/
 * compiler independent way.
 *
 * They also had an implicit "same size as pointer" characteristic
 * to them (i.e. Mach's traditional types are very ILP32 or ILP64
 * centric).  We will likely support x86 ABIs that do not follow
 * either ofthese models (specifically LP64).  Therefore, we had to
 * make a choice between making these types scale with pointers or stay
 * tied to integers.  Because their use is predominantly tied to
 * to the size of an integer, we are keeping that association and
 * breaking free from pointer size guarantees.
 *
 * New use of these types is discouraged.
 */
typedef __darwin_natural_t	natural_t;
typedef int			integer_t;

/*
 * A vm_offset_t is a type-neutral pointer,
 * e.g. an offset into a virtual memory space.
 */
typedef	natural_t		vm_offset_t;

/*
 * A vm_size_t is the proper type for e.g.
 * expressing the difference between two
 * vm_offset_t entities.
 */
typedef	natural_t		vm_size_t;

/*
 * This new type is independent of a particular vm map's
 * implementation size - and represents appropriate types
 * for all possible maps.  This is used for interfaces
 * where the size of the map is not known - or we don't
 * want to have to distinguish.
 */
#if defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && (__IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_5_0)
typedef uint32_t		mach_vm_address_t;
typedef uint32_t		mach_vm_offset_t;
typedef uint32_t		mach_vm_size_t;
#else
typedef uint64_t		mach_vm_address_t;
typedef uint64_t		mach_vm_offset_t;
typedef uint64_t		mach_vm_size_t;
#endif

typedef uint32_t		vm_map_offset_t;
typedef uint32_t		vm_map_address_t;
typedef uint32_t		vm_map_size_t;

typedef uint32_t		vm32_offset_t;
typedef uint32_t		vm32_address_t;
typedef uint32_t		vm32_size_t;

typedef vm_offset_t 		mach_port_context_t;

#define VM_MAP_MIN_ADDRESS	VM_MIN_ADDRESS
#define VM_MAP_MAX_ADDRESS	VM_MAX_ADDRESS

#endif	/* ASSEMBLER */

/*
 * If composing messages by hand (please do not)
 */
#define	MACH_MSG_TYPE_INTEGER_T	MACH_MSG_TYPE_INTEGER_32

#endif	/* _MACH_ARM_VM_TYPES_H_ */
