/**
  ******************************************************************************
  * @file    ADC/TIMTrigger_AutoInjection/main.c 
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
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup ADC_TIMTrigger_AutoInjection
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    ADC_InitTypeDef ADC_InitStructure;





    /* Private function prototypes ----------------------------------------------- */ 
void RCC_Configuration (void);






    /* Private functions --------------------------------------------------------- */ 
    
/**
  * @brief   Main program
  * @param  None
  * @retval None
  */ 
int main (void) 
{
    
        /* !< At this stage the microcontroller clock setting is already configured, 
           from startup
           function, refer to
        
        /* System clocks configuration --------------------------------------------- */ 
        RCC_Configuration ();
    
        /* NVIC configuration ------------------------------------------------------ */ 
        NVIC_Configuration ();
    
        /* GPIO configuration ------------------------------------------------------ */ 
        GPIO_Configuration ();
    
        /* TIM1 configuration ------------------------------------------------------ */ 
        /* Time Base configuration */ 
        TIM_TimeBaseStructInit (&TIM_TimeBaseStructure);
    
    
    
    
    
    
        /* TIM1 channel1 configuration in PWM mode */ 
        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    
    
    
    
    
        /* DMA1 Channel1 Configuration ---------------------------------------------- */ 
        DMA_DeInit (DMA1_Channel1);
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* Enable DMA1 channel1 */ 
        DMA_Cmd (DMA1_Channel1, ENABLE);
    
        /* ADC1 configuration ------------------------------------------------------ */ 
        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    
    
    
    
    
    
    
        /* ADC1 regular channel14 configuration */ 
        ADC_RegularChannelConfig (ADC1, ADC_Channel_14, 1, ADC_SampleTime_13Cycles5);
    
        /* Set injected sequencer length */ 
        ADC_InjectedSequencerLengthConfig (ADC1, 1);
    
        /* ADC1 injected channel Configuration */ 
        ADC_InjectedChannelConfig (ADC1, ADC_Channel_11, 1, ADC_SampleTime_71Cycles5);
    
        /* ADC1 injected external trigger configuration */ 
        ADC_ExternalTrigInjectedConvConfig (ADC1, ADC_ExternalTrigInjecConv_None);
    
        /* Enable automatic injected conversion start after regular one */ 
        ADC_AutoInjectedConvCmd (ADC1, ENABLE);
    
        /* Enable ADC1 DMA */ 
        ADC_DMACmd (ADC1, ENABLE);
    
        /* Enable ADC1 external trigger */ 
        ADC_ExternalTrigConvCmd (ADC1, ENABLE);
    
        /* Enable JEOC interupt */ 
        ADC_ITConfig (ADC1, ADC_IT_JEOC, ENABLE);
    
        /* Enable ADC1 */ 
        ADC_Cmd (ADC1, ENABLE);
    
        /* Enable ADC1 reset calibaration register */ 
        ADC_ResetCalibration (ADC1);
    
        /* Check the end of ADC1 reset calibration register */ 
        while (ADC_GetResetCalibrationStatus (ADC1));
    
        /* Start ADC1 calibaration */ 
        ADC_StartCalibration (ADC1);
    
        /* Check the end of ADC1 calibration */ 
        while (ADC_GetCalibrationStatus (ADC1));
    
        /* TIM1 counter enable */ 
        TIM_Cmd (TIM1, ENABLE);
    
        /* TIM1 main Output Enable */ 
        TIM_CtrlPWMOutputs (TIM1, ENABLE);
    
        /* Test on channel1 transfer complete flag */ 
        while (!DMA_GetFlagStatus (DMA1_FLAG_TC1));
    
        /* Clear channel1 transfer complete flag */ 
        DMA_ClearFlag (DMA1_FLAG_TC1);
    
        /* TIM1 counter disable */ 
        TIM_Cmd (TIM1, DISABLE);
    
        
    {
    



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL)
        /* ADCCLK = PCLK2/2 */ 
        RCC_ADCCLKConfig (RCC_PCLK2_Div2);
    
#else /* 
        /* ADCCLK = PCLK2/4 */ 
        RCC_ADCCLKConfig (RCC_PCLK2_Div4);
    
#endif /* 
        /* Enable peripheral clocks ------------------------------------------------ */ 
        /* Enable DMA1 clock */ 
        RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1, ENABLE);
    
        /* Enable GPIOA, GPIOC, ADC1 and TIM1 clock */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | 


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
        /* Configure TIM1_CH1 (PA8) as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    
    
    
    
        /* Configure PC.06 as output push-pull */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    
    
    
        /* Configure PC.01 and PC.04 (ADC Channel11 and Channel14) as analog input */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4;
    
    


/**
  * @brief  Configures NVIC and Vector Table base location.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* Configure and enable ADC interrupt */ 
#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL)
        NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn;
    
#else /* 
        NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
    
#endif /* 
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    
    
    


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