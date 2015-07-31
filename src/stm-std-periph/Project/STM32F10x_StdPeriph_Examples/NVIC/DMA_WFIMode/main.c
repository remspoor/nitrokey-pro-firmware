/**
  ******************************************************************************
  * @file    NVIC/DMA_WFIMode/main.c 
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
    
/** @addtogroup NVIC_DMA_WFIMode
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* Private define ------------------------------------------------------------ */ 
#ifdef USE_STM3210C_EVAL
#define USARTy_DR_Address    0x40004404
#define USARTy_DMA1_Channel  DMA1_Channel6
#define USARTy_DMA1_IRQn     DMA1_Channel6_IRQn
#else /* 
#define USARTy_DR_Address    0x40013804
#define USARTy_DMA1_Channel  DMA1_Channel5
#define USARTy_DMA1_IRQn     DMA1_Channel5_IRQn
#endif /* 
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    NVIC_InitTypeDef NVIC_InitStructure;




{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


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
    
        /* Initialize Leds and Key Button mounted on STM3210X-EVAL board */ 
        STM_EVAL_LEDInit (LED1);
    
    
    
    
    
        /* Configures the DMA Channel */ 
        DMA_Configuration ();
    
        /* EVAL_COM1 configuration --------------------------------------------------- */ 
        /* EVAL_COM1 configured as follow:
           disabled (RTS and CTS signals)
        USART_InitStructure.USART_BaudRate = 115200;
    
    
    
    
    
    
    
    
    
        /* Enable the USARTy_DMA1_IRQn Interrupt */ 
        NVIC_InitStructure.NVIC_IRQChannel = USARTy_DMA1_IRQn;
    
    
    
    
    
        /* Enable the EXTI9_5 Interrupt */ 
        NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    
    
    
        
    {
        
            
        {
            
            
            
                /* Request to enter WFI mode */ 
                __WFI ();
            
        
        
        
    



/**
  * @brief  Configures the different system clocks
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* DMA1 clock enable */ 
        RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1, ENABLE);


/**
  * @brief  Configures the used DMA Channel.
  * @param  None
  * @retval None
  */ 
void DMA_Configuration (void) 
{
    
    
        /* USARTy_DMA1_Channel Config */ 
        DMA_DeInit (USARTy_DMA1_Channel);
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* Enable USARTy_DMA1_Channel Transfer complete interrupt */ 
        DMA_ITConfig (USARTy_DMA1_Channel, DMA_IT_TC, ENABLE);
    
        /* USARTy_DMA1_Channel enable */ 
        DMA_Cmd (USARTy_DMA1_Channel, ENABLE);


/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 0: pBuffer1 identical to pBuffer2
  *           1: pBuffer1 differs from pBuffer2
  */ 
    uint8_t Buffercmp16 (uint16_t * pBuffer1, uint16_t * pBuffer2, uint16_t BufferLength) 
{
    
        
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