/**
  ******************************************************************************
  * @file    NVIC/IRQ_Channels/main.c 
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
    
/** @addtogroup NVIC_IRQ_Channels
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Private function prototypes ----------------------------------------------- */ 
void RCC_Configuration (void);




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
        
        /* Configure the system clocks */ 
        RCC_Configuration ();
    
        /* Initialize Leds mounted on STM3210X-EVAL board */ 
        STM_EVAL_LEDInit (LED1);
    
    
    
    
        /* Configure TIMs */ 
        TIM_Configuration ();
    
        /* Configure two bits for preemption priority */ 
        NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2);
    
        /* Enable the TIM2 Interrupt */ 
        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    
    
    
    
    
        /* Enable the TIM3 Interrupt */ 
        NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    
    
    
        /* Enable the TIM4 Interrupt */ 
        NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    
    
    
        
    {
    



/**
  * @brief  Configures the different system clocks
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* Enable TIM2, TIM3 and TIM4 clocks */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | 


/**
  * @brief  Configures the used Timers.
  * @param  None
  * @retval None
  */ 
void TIM_Configuration (void) 
{
    
    
    
        /* TIM2 configuration */ 
        TIM_TimeBaseStructure.TIM_Period = 0x4AF;
    
    
    
    
    
    
    
        /* Output Compare Timing Mode configuration: Channel1 */ 
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    
    
    
        /* TIM3 configuration */ 
        TIM_TimeBaseStructure.TIM_Period = 0x95F;
    
    
        /* Output Compare Timing Mode configuration: Channel1 */ 
        TIM_OC1Init (TIM3, &TIM_OCInitStructure);
    
        /* TIM4 configuration */ 
        TIM_TimeBaseStructure.TIM_Period = 0xE0F;
    
    
        /* Output Compare Timing Mode configuration: Channel1 */ 
        TIM_OC1Init (TIM4, &TIM_OCInitStructure);
    
        /* TIM2 enable counter */ 
        TIM_Cmd (TIM2, ENABLE);
    
        /* TIM3 enable counter */ 
        TIM_Cmd (TIM3, ENABLE);
    
        /* TIM4 enable counter */ 
        TIM_Cmd (TIM4, ENABLE);
    
        /* Immediate load of TIM2 Precaler value */ 
        TIM_PrescalerConfig (TIM2, ((SystemCoreClock / 1200) - 1), TIM_PSCReloadMode_Immediate);
    
        /* Immediate load of TIM3 Precaler value */ 
        TIM_PrescalerConfig (TIM3, ((SystemCoreClock / 1200) - 1), TIM_PSCReloadMode_Immediate);
    
        /* Immediate load of TIM4 Precaler value */ 
        TIM_PrescalerConfig (TIM4, ((SystemCoreClock / 1200) - 1), TIM_PSCReloadMode_Immediate);
    
        /* Clear TIM2 update pending flag */ 
        TIM_ClearFlag (TIM2, TIM_FLAG_Update);
    
        /* Clear TIM3 update pending flag */ 
        TIM_ClearFlag (TIM3, TIM_FLAG_Update);
    
        /* Clear TIM4 update pending flag */ 
        TIM_ClearFlag (TIM4, TIM_FLAG_Update);
    
        /* Enable TIM2 Update interrupt */ 
        TIM_ITConfig (TIM2, TIM_IT_Update, ENABLE);
    
        /* Enable TIM3 Update interrupt */ 
        TIM_ITConfig (TIM3, TIM_IT_Update, ENABLE);
    
        /* Enable TIM4 Update interrupt */ 
        TIM_ITConfig (TIM4, TIM_IT_Update, ENABLE);


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