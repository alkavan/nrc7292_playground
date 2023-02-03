/*
    FreeRTOS V8.0.0 - Copyright (C) 2014 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that has become a de facto standard.             *
     *                                                                       *
     *    Help yourself get started quickly and support the FreeRTOS         *
     *    project by purchasing a FreeRTOS tutorial book, reference          *
     *    manual, or both from: http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    Thank you!                                                         *
     *                                                                       *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    >>! NOTE: The modification to the GPL is included to allow you to distribute
    >>! a combined work that includes FreeRTOS without being obliged to provide
    >>! the source code for proprietary components outside of the FreeRTOS
    >>! kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available from the following
    link: http://www.freertos.org/a00114.html

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - Documentation, books, training, latest versions,
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef PORTMACRO_H
#define PORTMACRO_H

#include "nds32_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------
 * Port specific definitions.  
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR		char
#define portFLOAT		float
#define portDOUBLE		double
#define portLONG		long
#define portSHORT		short
#define portSTACK_TYPE		unsigned portLONG
#define portBASE_TYPE		portLONG

typedef portSTACK_TYPE StackType_t;
typedef portLONG BaseType_t;
typedef unsigned portLONG UBaseType_t;


#if( configUSE_16_BIT_TICKS == 1 )	
	typedef unsigned portSHORT TickType_t;
	#define portMAX_DELAY ( portTickType ) 0xffff
#else
	typedef unsigned portLONG TickType_t;
	#define portMAX_DELAY ( portTickType ) 0xffffffff
#endif
/*-----------------------------------------------------------*/	

/* Architecture specifics. */
#define portSTACK_GROWTH		( -1 )
//#define portTICK_RATE_MS		( ( portTickType ) 1000 / configTICK_RATE_HZ )		
#define portTICK_PERIOD_MS             ( ( portTickType ) 1000 / configTICK_RATE_HZ )
#ifdef MPU_SUPPORT
#define portBYTE_ALIGNMENT		4096
#define portBYTE_ALIGNMENT_MASK ( portBYTE_ALIGNMENT-1 )
#else
#define portBYTE_ALIGNMENT		32
/*
 * KJW - in v9.0.0 portBYTE_ALIGNMENT_MASK is defined in portable.h
 */
#if 0
#if( portBYTE_ALIGNMENT == 32 || portBYTE_ALIGNMENT == 16)
	#define portBYTE_ALIGNMENT_MASK ( portBYTE_ALIGNMENT-1 )
#endif
#endif
#endif


#define portNOP()			asm volatile ( "nop" );
/*-----------------------------------------------------------*/	

#include "os_cpu.h"
extern OS_CPU_SR psw_1;

/* Scheduler utilities. */
#define portRESTORE_CONTEXT		CtxRestore		
#define portSAVE_CONTEXT		CtxSave

void vPortYield();
#define portYIELD()			vPortYield()
#define portYIELD_FROM_ISR( xSwitchRequired ) if( xSwitchRequired ) vPortYield()

/* Critical section management. */

#define portDISABLE_INTERRUPTS()	do{ GIE_SAVE( &psw_1);} while(0)
#define portENABLE_INTERRUPTS()		do{ GIE_RESTORE(psw_1);} while(0)

void vPortEnterCritical();
void vPortExitCritical();

#define portENTER_CRITICAL()     	vPortEnterCritical()
#define portEXIT_CRITICAL()     	vPortExitCritical()

/* Kernel_API_From_ISR barrier */
/* If is the priority interrupt, should changed into mask & unmask */
/* Since Fixed priority interrupt, just disable interrupt */
extern unsigned long ulPortSetInterruptMask();
extern void vPortClearInterruptMask( unsigned long ulNewMaskValue );
#define portSET_INTERRUPT_MASK_FROM_ISR()	ulPortSetInterruptMask()	
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x)	vPortClearInterruptMask(x)

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )

/* trace macro define */
//#define traceTASK_SWITCHED_IN() vPortSwitchIn()  
//#define traceTASK_SWITCHED_OUT() vPortSwitchOut()

#ifdef MPU_SUPPORT
/*-----------------------------------------------------------*/

	/* MPU specific constants. */
	#define portUSING_MPU_WRAPPERS	1
	#define portPRIVILEGE_BIT                       	( 0x80000000 )
	#define portMPU_REGION_READ_WRITE                       ( 0x03 << 24 )
	#define portMPU_REGION_PRIVILEGED_READ_ONLY             ( 0x05 << 24 )
	#define portMPU_REGION_READ_ONLY                        ( 0x06 << 24 )
	#define portMPU_REGION_PRIVILEGED_READ_WRITE    	( 0x01 << 24 )
	#define portMPU_REGION_CACHEABLE_BUFFERABLE             ( 0x07 << 16 )
	#define portMPU_REGION_EXECUTE_NEVER                    ( 0x01 << 28 )

	#define portFIRST_CONFIGURABLE_REGION       		( 3 )
	#define portLAST_CONFIGURABLE_REGION            	( 7 )
	#define portNUM_CONFIGURABLE_REGIONS            	( 3 )
	#define portTOTAL_NUM_REGIONS                           ( portNUM_CONFIGURABLE_REGIONS + 1 ) /* Plus one to make space for the stack region. */

	#define portSWITCH_TO_USER_MODE() __asm__ volatile ( " mfsr $r0, $PSW \n bclr $r0, $r0, %0\n mtsr $r0, $PSW\n dsb\n " ::"i" (PSW_offPOM):"$r0" )

	typedef struct MPU_REGION_ENTRY {
        	unsigned portLONG ulPA;
        	unsigned portLONG ulSize;
		unsigned portLONG ulAttr;
		unsigned portLONG ulTLB_DATA;
		unsigned portLONG ulTLB_VPN;
	} xMPU_REGION_ENTRY;

	/* Plus 1 to create space for the stack region. */
	typedef struct MPU_SETTINGS {
	        xMPU_REGION_ENTRY xRegion[ portTOTAL_NUM_REGIONS ];
	} xMPU_SETTINGS;
#else
/*------------------------------------------------------------*/

/* Tickless idle/low power functionality. */
#ifndef portSUPPRESS_TICKS_AND_SLEEP
	extern void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );
	#define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime ) vPortSuppressTicksAndSleep( xExpectedIdleTime )
#endif
#endif

/*------------------------------------------------------------*/

/* Architecture specific optimisations. */
/* Optimize highest priority task selection of scheduler */
#if ( configUSE_PORT_OPTIMISED_TASK_SELECTION == 1 )
	#ifdef __NDS32_ISA_V3M__
		#error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set 1 when ISA has performance extension instruction.\
			Do not support on __NDS32_ISA_V3M__.
	#endif
	/* Generic helper function. */
	__attribute__( ( always_inline ) )static inline unsigned char ucPortCountLeadingZeros( unsigned long ulBitmap )
	{
	unsigned char ucReturn;

		__asm volatile ( "clz %0, %1" : "=r" ( ucReturn ) : "r" ( ulBitmap ) );
		return ucReturn;
	}
	/* Check the configuration. */

	#if ( configMAX_PRIORITIES > 32 )

		 #error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.\
	It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
	#endif


	/* Store/clear the ready priorities in a bit map. */
	#define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
	#define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

	/*-----------------------------------------------------------*/
	
	#define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31 - ucPortCountLeadingZeros( ( uxReadyPriorities ) ) )


#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */



#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */

