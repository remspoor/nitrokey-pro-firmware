/**
  ******************************************************************************
  * @file    TIM/TimeBase/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
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
#include "stm32f10x_it.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup TIM_TimeBase
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    uint16_t capture = 0;









    /* Private function prototypes ----------------------------------------------- */ 
    /* Private functions --------------------------------------------------------- */ 
    
/******************************************************************************/ 
    /* Cortex-M3 Processor Exceptions Handlers */ 
/******************************************************************************/ 
    
/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */ 
void NMI_Handler (void) 
{


/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */ 
void HardFault_Handler (void) 
{
    
        /* Go to infinite loop when Hard Fault exception occurs */ 
        while (1)
        
    {
    }



/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */ 
void MemManage_Handler (void) 
{
    
        /* Go to infinite loop when Memory Manage exception occurs */ 
        while (1)
        
    {
    }



/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */ 
void BusFault_Handler (void) 
{
    
        /* Go to infinite loop when Bus Fault exception occurs */ 
        while (1)
        
    {
    }



/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */ 
void UsageFault_Handler (void) 
{
    
        /* Go to infinite loop when Usage Fault exception occurs */ 
        while (1)
        
    {
    }



/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */ 
void DebugMon_Handler (void) 
{
} 

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */ 
void SVC_Handler (void) 
{
} 

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */ 
void PendSV_Handler (void) 
{
} 

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */ 
void SysTick_Handler (void) 
{
} 

/******************************************************************************/ 
    /* STM32F10x Peripherals Interrupt Handlers */ 
/******************************************************************************/ 
    
/**
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval None
  */ 
void TIM2_IRQHandler (void) 
{
    
        
    {
        
        
            /* Pin PC.06 toggling with frequency = 73.24 Hz */ 
            GPIO_WriteBit (GPIOC, GPIO_Pin_6, (BitAction) (1 - GPIO_ReadOutputDataBit (GPIOC, GPIO_Pin_6)));
        
        
    
    
    else if (TIM_GetITStatus (TIM2, TIM_IT_CC2) != RESET)
        
    {
        
        
            /* Pin PC.07 toggling with frequency = 109.8 Hz */ 
            GPIO_WriteBit (GPIOC, GPIO_Pin_7, (BitAction) (1 - GPIO_ReadOutputDataBit (GPIOC, GPIO_Pin_7)));
        
        
    
    
    else if (TIM_GetITStatus (TIM2, TIM_IT_CC3) != RESET)
        
    {
        
        
            /* Pin PC.08 toggling with frequency = 219.7 Hz */ 
            GPIO_WriteBit (GPIOC, GPIO_Pin_8, (BitAction) (1 - GPIO_ReadOutputDataBit (GPIOC, GPIO_Pin_8)));
        
        
    
    
    else
        
    {
        
        
            /* Pin PC.09 toggling with frequency = 439.4 Hz */ 
            GPIO_WriteBit (GPIOC, GPIO_Pin_9, (BitAction) (1 - GPIO_ReadOutputDataBit (GPIOC, GPIO_Pin_9)));
        
        
    



/******************************************************************************/ 
    /* STM32F10x Peripherals Interrupt Handlers */ 
    /* Add here the Interrupt Handler for the used peripheral(s) (PPP), for the */ 
    /* available peripheral interrupt handler's name please refer to the startup */ 
    /* file (startup_stm32f10x_xx.s).  */ 
/******************************************************************************/ 
    
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */ 
    /* void PPP_IRQHandler(void)
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 