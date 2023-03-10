/*
 * Copyright (c) 2000-2010 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * @OSF_COPYRIGHT@
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
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
 *	File:	mach/task_special_ports.h
 *
 *	Defines codes for special_purpose task ports.  These are NOT
 *	port identifiers - they are only used for the task_get_special_port
 *	and task_set_special_port routines.
 *	
 */

#ifndef	_MACH_TASK_SPECIAL_PORTS_H_
#define _MACH_TASK_SPECIAL_PORTS_H_

typedef	int	task_special_port_t;

#define TASK_KERNEL_PORT	1	/* Represents task to the outside
					   world.*/

#define TASK_HOST_PORT		2	/* The host (priv) port for task.  */

#define TASK_NAME_PORT		3	/* the name (unpriv) port for task */

#define TASK_BOOTSTRAP_PORT	4	/* Bootstrap environment for task. */

/*
 * Evolving and likely to change.
 */

#define TASK_SEATBELT_PORT	7	/* Seatbelt compiler/DEM port for task. */

#define TASK_GSSD_PORT		8	/* GSSD port for security context */

#define TASK_ACCESS_PORT	9	/* Permission check for task_for_pid. */


/*
 *	Definitions for ease of use
 */

#define task_get_kernel_port(task, port)	\
		(task_get_special_port((task), TASK_KERNEL_PORT, (port)))

#define task_set_kernel_port(task, port)	\
		(task_set_special_port((task), TASK_KERNEL_PORT, (port)))

#define task_get_host_port(task, port)		\
		(task_get_special_port((task), TASK_HOST_PORT, (port)))

#define task_set_host_port(task, port)	\
		(task_set_special_port((task), TASK_HOST_PORT, (port)))

#define task_get_bootstrap_port(task, port)	\
		(task_get_special_port((task), TASK_BOOTSTRAP_PORT, (port)))

#define task_set_bootstrap_port(task, port)	\
		(task_set_special_port((task), TASK_BOOTSTRAP_PORT, (port)))

#define task_get_gssd_port(task, port)	\
		(task_get_special_port((task), TASK_GSSD_PORT, (port)))

#define task_set_gssd_port(task, port)	\
		(task_set_special_port((task), TASK_GSSD_PORT, (port)))

#define task_get_task_access_port(task, port)	\
		(task_get_special_port((task), TASK_ACCESS_PORT, (port)))

#define task_set_task_access_port(task, port)	\
		(task_set_special_port((task), TASK_ACCESS_PORT, (port)))

#endif	/* _MACH_TASK_SPECIAL_PORTS_H_ */
