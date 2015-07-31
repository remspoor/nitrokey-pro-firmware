/**
  ******************************************************************************
  * @file    NVIC/Priority/main.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main program body
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
#include "stm32_eval.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup NVIC_Priority
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    NVIC_InitTypeDef NVIC_InitStructure;



    /* Private function prototypes ----------------------------------------------- */ 
void Delay (__IO uint32_t nCount);


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
        
        /* Initialize LED1..LED4, Key and Wakeup Buttons mounted on STM3210X-EVAL 
        STM_EVAL_LEDInit (LED1);
    
    
    
    
    
    
        /* Configure one bit for preemption priority */ 
        NVIC_PriorityGroupConfig (NVIC_PriorityGroup_1);
    
        /* Enable the WAKEUP_BUTTON_EXTI_IRQn Interrupt */ 
        NVIC_InitStructure.NVIC_IRQChannel = WAKEUP_BUTTON_EXTI_IRQn;
    
    
    
    
    
        /* Enable the KEY_BUTTON_EXTI_IRQn Interrupt */ 
        NVIC_InitStructure.NVIC_IRQChannel = KEY_BUTTON_EXTI_IRQn;
    
    
    
    
    
        /* Configure the SysTick Handler Priority: Preemption priority and subpriority */ 
        NVIC_SetPriority (SysTick_IRQn, NVIC_EncodePriority (NVIC_GetPriorityGrouping (), !PreemptionPriorityValue, 0));
    
        
    {
        
            
        {
            
            
            
            
            
            
            
            
        
    



/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */ 
void Delay (__IO uint32_t nCount) 
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