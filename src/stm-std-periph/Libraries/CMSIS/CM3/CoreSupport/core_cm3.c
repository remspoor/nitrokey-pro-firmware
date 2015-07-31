                                                                                                                                                                                                                                                                                                                                                                                                                                                                        /**************************************************************************//**
 * @file     core_cm3.c
 * @brief    CMSIS Cortex-M3 Core Peripheral Access Layer Source File
 * @version  V1.30
 * @date     30. October 2009
 *
 * @note
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#include <stdint.h>
    
    /* define compiler specific symbols */ 
#if defined ( __CC_ARM   )
#define __ASM            __asm                                      /*!< asm keyword for ARM Compiler          */
#define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler       */
    
#elif defined ( __ICCARM__ )
#define __ASM           __asm                                       /*!< asm keyword for IAR Compiler          */
#define __INLINE        inline                                      /*!< inline keyword for IAR Compiler. Only avaiable in High optimization mode! */
    
#elif defined   (  __GNUC__  )
#define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
#define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */
    
#elif defined   (  __TASKING__  )
#define __ASM            __asm                                      /*!< asm keyword for TASKING Compiler      */
#define __INLINE         inline                                     /*!< inline keyword for TASKING Compiler   */
    
#endif /* 
    
    /* ################### Compiler specific Intrinsics ########################### */ 
    
#if defined ( __CC_ARM   ) /*------------------RealView Compiler -----------------*/
    /* ARM armcc specific functions */ 
    
/**
 * @brief  Return the Process Stack Pointer
 *
 * @return ProcessStackPointer
 *
 * Return the actual process stack pointer
 */ 
    __ASM uint32_t __get_PSP (void) 
{


/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  topOfProcStack  Process Stack Pointer
 *
 * Assign the value ProcessStackPointer to the MSP 
 * (process stack pointer) Cortex processor register
 */ 
__ASM void __set_PSP (uint32_t topOfProcStack) 
{


/**
 * @brief  Return the Main Stack Pointer
 *
 * @return Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */ 
    __ASM uint32_t __get_MSP (void) 
{


/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  topOfMainStack  Main Stack Pointer
 *
 * Assign the value mainStackPointer to the MSP 
 * (main stack pointer) Cortex processor register
 */ 
__ASM void __set_MSP (uint32_t mainStackPointer) 
{


/**
 * @brief  Reverse byte order in unsigned short value
 *
 * @param   value  value to reverse
 * @return         reversed value
 *
 * Reverse byte order in unsigned short value
 */ 
    __ASM uint32_t __REV16 (uint16_t value) 
{


/**
 * @brief  Reverse byte order in signed short value with sign extension to integer
 *
 * @param   value  value to reverse
 * @return         reversed value
 *
 * Reverse byte order in signed short value with sign extension to integer
 */ 
    __ASM int32_t __REVSH (int16_t value) 
{


#if (__ARMCC_VERSION < 400000)
    
/**
 * @brief  Remove the exclusive lock created by ldrex
 *
 * Removes the exclusive lock which is created by ldrex.
 */ 
__ASM void __CLREX (void) 
{


/**
 * @brief  Return the Base Priority value
 *
 * @return BasePriority
 *
 * Return the content of the base priority register
 */ 
    __ASM uint32_t __get_BASEPRI (void) 
{


/**
 * @brief  Set the Base Priority value
 *
 * @param  basePri  BasePriority
 *
 * Set the base priority register
 */ 
__ASM void __set_BASEPRI (uint32_t basePri) 
{


/**
 * @brief  Return the Priority Mask value
 *
 * @return PriMask
 *
 * Return state of the priority mask bit from the priority mask register
 */ 
    __ASM uint32_t __get_PRIMASK (void) 
{


/**
 * @brief  Set the Priority Mask value
 *
 * @param  priMask  PriMask
 *
 * Set the priority mask bit in the priority mask register
 */ 
__ASM void __set_PRIMASK (uint32_t priMask) 
{


/**
 * @brief  Return the Fault Mask value
 *
 * @return FaultMask
 *
 * Return the content of the fault mask register
 */ 
    __ASM uint32_t __get_FAULTMASK (void) 
{


/**
 * @brief  Set the Fault Mask value
 *
 * @param  faultMask  faultMask value
 *
 * Set the fault mask register
 */ 
__ASM void __set_FAULTMASK (uint32_t faultMask) 
{


/**
 * @brief  Return the Control Register value
 * 
 * @return Control value
 *
 * Return the content of the control register
 */ 
    __ASM uint32_t __get_CONTROL (void) 
{


/**
 * @brief  Set the Control Register value
 *
 * @param  control  Control value
 *
 * Set the control register
 */ 
__ASM void __set_CONTROL (uint32_t control) 
{

#endif  /* __ARMCC_VERSION  */ 
    
#elif (defined (__ICCARM__)) /*------------------ ICC Compiler -------------------*/
    /* IAR iccarm specific functions */ 
#pragma diag_suppress=Pe940
    
/**
 * @brief  Return the Process Stack Pointer
 *
 * @return ProcessStackPointer
 *
 * Return the actual process stack pointer
 */ 
    uint32_t __get_PSP (void) 
{
    
    


/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  topOfProcStack  Process Stack Pointer
 *
 * Assign the value ProcessStackPointer to the MSP 
 * (process stack pointer) Cortex processor register
 */ 
void __set_PSP (uint32_t topOfProcStack) 
{
    
    


/**
 * @brief  Return the Main Stack Pointer
 *
 * @return Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */ 
    uint32_t __get_MSP (void) 
{
    
    


/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  topOfMainStack  Main Stack Pointer
 *
 * Assign the value mainStackPointer to the MSP 
 * (main stack pointer) Cortex processor register
 */ 
void __set_MSP (uint32_t topOfMainStack) 
{
    
    


/**
 * @brief  Reverse byte order in unsigned short value
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in unsigned short value
 */ 
    uint32_t __REV16 (uint16_t value) 
{
    
    


/**
 * @brief  Reverse bit order of value
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse bit order of value
 */ 
    uint32_t __RBIT (uint32_t value) 
{
    
    


/**
 * @brief  LDR Exclusive (8 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 8 bit values)
 */ 
    uint8_t __LDREXB (uint8_t * addr) 
{
    
    


/**
 * @brief  LDR Exclusive (16 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 16 bit values
 */ 
    uint16_t __LDREXH (uint16_t * addr) 
{
    
    


/**
 * @brief  LDR Exclusive (32 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 32 bit values
 */ 
    uint32_t __LDREXW (uint32_t * addr) 
{
    
    


/**
 * @brief  STR Exclusive (8 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 8 bit values
 */ 
    uint32_t __STREXB (uint8_t value, uint8_t * addr) 
{
    
    


/**
 * @brief  STR Exclusive (16 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 16 bit values
 */ 
    uint32_t __STREXH (uint16_t value, uint16_t * addr) 
{
    
    


/**
 * @brief  STR Exclusive (32 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 32 bit values
 */ 
    uint32_t __STREXW (uint32_t value, uint32_t * addr) 
{
    
    


#pragma diag_default=Pe940
    
#elif (defined (__GNUC__)) /*------------------ GNU Compiler ---------------------*/
    /* GNU gcc specific functions */ 
    
/**
 * @brief  Return the Process Stack Pointer
 *
 * @return ProcessStackPointer
 *
 * Return the actual process stack pointer
 */ 
    uint32_t __get_PSP (void) __attribute__ ((naked));


{
    
    
    



/**
 * @brief  Set the Process Stack Pointer
 *
 * @param  topOfProcStack  Process Stack Pointer
 *
 * Assign the value ProcessStackPointer to the MSP 
 * (process stack pointer) Cortex processor register
 */ 
void __set_PSP (uint32_t topOfProcStack) __attribute__ ((naked));


{



/**
 * @brief  Return the Main Stack Pointer
 *
 * @return Main Stack Pointer
 *
 * Return the current value of the MSP (main stack pointer)
 * Cortex processor register
 */ 
    uint32_t __get_MSP (void) __attribute__ ((naked));


{
    
    
    



/**
 * @brief  Set the Main Stack Pointer
 *
 * @param  topOfMainStack  Main Stack Pointer
 *
 * Assign the value mainStackPointer to the MSP 
 * (main stack pointer) Cortex processor register
 */ 
void __set_MSP (uint32_t topOfMainStack) __attribute__ ((naked));


{



/**
 * @brief  Return the Base Priority value
 *
 * @return BasePriority
 *
 * Return the content of the base priority register
 */ 
    uint32_t __get_BASEPRI (void) 
{
    
    

    



/**
 * @brief  Set the Base Priority value
 *
 * @param  basePri  BasePriority
 *
 * Set the base priority register
 */ 
void __set_BASEPRI (uint32_t value) 
{



/**
 * @brief  Return the Priority Mask value
 *
 * @return PriMask
 *
 * Return state of the priority mask bit from the priority mask register
 */ 
    uint32_t __get_PRIMASK (void) 
{
    
    

    



/**
 * @brief  Set the Priority Mask value
 *
 * @param  priMask  PriMask
 *
 * Set the priority mask bit in the priority mask register
 */ 
void __set_PRIMASK (uint32_t priMask) 
{



/**
 * @brief  Return the Fault Mask value
 *
 * @return FaultMask
 *
 * Return the content of the fault mask register
 */ 
    uint32_t __get_FAULTMASK (void) 
{
    
    

    



/**
 * @brief  Set the Fault Mask value
 *
 * @param  faultMask  faultMask value
 *
 * Set the fault mask register
 */ 
void __set_FAULTMASK (uint32_t faultMask) 
{



/**
 * @brief  Return the Control Register value
* 
*  @return Control value
 *
 * Return the content of the control register
 */ 
    uint32_t __get_CONTROL (void) 
{
    
    

    



/**
 * @brief  Set the Control Register value
 *
 * @param  control  Control value
 *
 * Set the control register
 */ 
void __set_CONTROL (uint32_t control) 
{



/**
 * @brief  Reverse byte order in integer value
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in integer value
 */ 
    uint32_t __REV (uint32_t value) 
{
    


    



/**
 * @brief  Reverse byte order in unsigned short value
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in unsigned short value
 */ 
    uint32_t __REV16 (uint16_t value) 
{
    


    



/**
 * @brief  Reverse byte order in signed short value with sign extension to integer
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse byte order in signed short value with sign extension to integer
 */ 
    int32_t __REVSH (int16_t value) 
{
    


    



/**
 * @brief  Reverse bit order of value
 *
 * @param  value  value to reverse
 * @return        reversed value
 *
 * Reverse bit order of value
 */ 
    uint32_t __RBIT (uint32_t value) 
{
    


    



/**
 * @brief  LDR Exclusive (8 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 8 bit value
 */ 
    uint8_t __LDREXB (uint8_t * addr) 
{
    


    



/**
 * @brief  LDR Exclusive (16 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 16 bit values
 */ 
    uint16_t __LDREXH (uint16_t * addr) 
{
    


    



/**
 * @brief  LDR Exclusive (32 bit)
 *
 * @param  *addr  address pointer
 * @return        value of (*address)
 *
 * Exclusive LDR command for 32 bit values
 */ 
    uint32_t __LDREXW (uint32_t * addr) 
{
    


    



/**
 * @brief  STR Exclusive (8 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 8 bit values
 */ 
    uint32_t __STREXB (uint8_t value, uint8_t * addr) 
{
    

    



/**
 * @brief  STR Exclusive (16 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 16 bit values
 */ 
    uint32_t __STREXH (uint16_t value, uint16_t * addr) 
{
    

    



/**
 * @brief  STR Exclusive (32 bit)
 *
 * @param  value  value to store
 * @param  *addr  address pointer
 * @return        successful / failed
 *
 * Exclusive STR command for 32 bit values
 */ 
    uint32_t __STREXW (uint32_t value, uint32_t * addr) 
{
    


    



#elif (defined (__TASKING__)) /*------------------ TASKING Compiler ---------------------*/
    /* TASKING carm specific functions */ 
    
    /* 
       instrinsics,
    
#endif /* 