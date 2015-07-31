/**
  ******************************************************************************
  * @file    CortexM3/Mode_Privilege/main.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main program body.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */  
    
    /* Includes ------------------------------------------------------------------ */ 
#include "stm32f10x.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup CortexM3_Mode_Privilege
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
#define SP_PROCESS_SIZE             0x200  /* Process stack size */
#define SP_PROCESS                  0x02   /* Process stack */
#define SP_MAIN                     0x00   /* Main stack */
#define THREAD_MODE_PRIVILEGED      0x00   /* Thread mode has privileged access */
#define THREAD_MODE_UNPRIVILEGED    0x01   /* Thread mode has unprivileged access */
    
    /* Private macro ------------------------------------------------------------- */ 
#if defined ( __CC_ARM   )
__ASM void __SVC (void) 
{

#elif defined ( __ICCARM__ )
static __INLINE void __SVC ()
{
    __ASM ("svc 0x01");
} 
#elif defined   (  __GNUC__  )
static __INLINE void __SVC ()
{
__ASM volatile ("svc 0x01");
} 
#endif /* 
    
    /* Private variables --------------------------------------------------------- */ 
    __IO uint8_t PSPMemAlloc[SP_PROCESS_SIZE];


    /* Private function prototypes ----------------------------------------------- */ 
    /* Private functions --------------------------------------------------------- */ 
    
/**
  * @brief   Main program.
  * @param  None
  * @retval None
  */ 
int main (void) 
{
    
        /* !< At this stage the microcontroller clock setting is already configured, 
           from startup
           function, refer to
        
        /* Switch Thread mode Stack from Main to Process ----------------------------- */ 
        /* Initialize memory reserved for Process Stack */ 
        for (Index = 0; Index < SP_PROCESS_SIZE; Index++)
        
    {
        
    
    
        /* Set Process stack value */ 
        __set_PSP ((uint32_t) PSPMemAlloc + SP_PROCESS_SIZE);
    
        /* Select Process Stack as Thread mode Stack */ 
        __set_CONTROL (SP_PROCESS);
    
        /* Get the Thread mode stack used */ 
        if ((__get_CONTROL () & 0x02) == SP_MAIN)
        
    {
        
            /* Main stack is used as the current stack */ 
            CurrentStack = SP_MAIN;
    
    
    else
        
    {
        
            /* Process stack is used as the current stack */ 
            CurrentStack = SP_PROCESS;
        
            /* Get process stack pointer value */ 
            PSPValue = __get_PSP ();
    
    
        /* Switch Thread mode from privileged to unprivileged ------------------------ */ 
        /* Thread mode has unprivileged access */ 
        __set_CONTROL (THREAD_MODE_UNPRIVILEGED | SP_PROCESS);
    
        /* Unprivileged access mainly affect ability to:
           (SCS) registers such as NVIC and SysTick */ 
        
        /* Check Thread mode privilege status */ 
        if ((__get_CONTROL () & 0x01) == THREAD_MODE_PRIVILEGED)
        
    {
        
            /* Thread mode has privileged access */ 
            ThreadMode = THREAD_MODE_PRIVILEGED;
    
    
    else
        
    {
        
            /* Thread mode has unprivileged access */ 
            ThreadMode = THREAD_MODE_UNPRIVILEGED;
    
    
        /* Switch back Thread mode from unprivileged to privileged ------------------- */ 
        /* Try to switch back Thread mode to privileged (Not possible, this can be
        __set_CONTROL (THREAD_MODE_PRIVILEGED | SP_PROCESS);
    
        /* Generate a system call exception, and in the ISR switch back Thread mode
        __SVC ();
    
        /* Check Thread mode privilege status */ 
        if ((__get_CONTROL () & 0x01) == THREAD_MODE_PRIVILEGED)
        
    {
        
            /* Thread mode has privileged access */ 
            ThreadMode = THREAD_MODE_PRIVILEGED;
    
    
    else
        
    {
        
            /* Thread mode has unprivileged access */ 
            ThreadMode = THREAD_MODE_UNPRIVILEGED;
    
    
        
    {
    



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */ 
void assert_failed (uint8_t * file, uint32_t line) 
{
    
        /* User can add his own implementation to report the file name and line number,
           file, line) */ 
        
        /* Infinite loop */ 
        while (1)
        
    {
    



#endif /* 
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 