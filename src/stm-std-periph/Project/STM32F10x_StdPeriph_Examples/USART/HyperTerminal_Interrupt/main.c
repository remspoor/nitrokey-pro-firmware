/**
  ******************************************************************************
  * @file    USART/HyperTerminal_Interrupt/main.c 
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
    
/** @addtogroup USART_HyperTerminal_Interrupt
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
#ifdef USE_STM3210C_EVAL
#define USARTx_IRQn   USART2_IRQn
#else /* 
#define USARTx_IRQn   USART1_IRQn
#endif /* 
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    USART_InitTypeDef USART_InitStructure;

    /* Private function prototypes ----------------------------------------------- */ 
void NVIC_Configuration (void);


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
        
        /* NVIC configuration */ 
        NVIC_Configuration ();
    
        /* USARTx configuration ------------------------------------------------------ */ 
        /* USARTx configured as follow:
           disabled (RTS and CTS signals)
        USART_InitStructure.USART_BaudRate = 9600;
    
    
    
    
    
    
    
        /* Enable the EVAL_COM1 Transmoit interrupt: this interrupt is generated when the 
        USART_ITConfig (EVAL_COM1, USART_IT_TXE, ENABLE);
    
        /* Enable the EVAL_COM1 Receive interrupt: this interrupt is generated when the 
        USART_ITConfig (EVAL_COM1, USART_IT_RXNE, ENABLE);
    
        
    {
    



/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* Enable the USARTx Interrupt */ 
        NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
    
    
    
    


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