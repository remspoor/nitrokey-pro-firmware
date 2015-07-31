/**
  ******************************************************************************
  * @file    SPI/Simplex_Interrupt/main.c 
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
#include "platform_config.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup SPI_Simplex_Interrupt
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
#define BufferSize 32
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    SPI_InitTypeDef SPI_InitStructure;

{
0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
        





    /* Private functions --------------------------------------------------------- */ 
void RCC_Configuration (void);







/**
  * @brief  Main program
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
    
        /* SPI_MASTER configuration ------------------------------------------------ */ 
        SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    
    
    
    
    
    
    
    
    
    
        /* SPI_SLAVE configuration ------------------------------------------------- */ 
        SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Rx;
    
    
    
        /* Enable SPI_MASTER TXE interrupt */ 
        SPI_I2S_ITConfig (SPI_MASTER, SPI_I2S_IT_TXE, ENABLE);
    
        /* Enable SPI_SLAVE RXNE interrupt */ 
        SPI_I2S_ITConfig (SPI_SLAVE, SPI_I2S_IT_RXNE, ENABLE);
    
        /* Enable SPI_SLAVE */ 
        SPI_Cmd (SPI_SLAVE, ENABLE);
    
        /* Enable SPI_MASTER */ 
        SPI_Cmd (SPI_MASTER, ENABLE);
    
        /* Transfer procedure */ 
        while (RxIdx < BufferSize)
        
    {
    }
    
        /* Check the corectness of written dada */ 
        TransferStatus = Buffercmp (SPI_SLAVE_Buffer_Rx, SPI_MASTER_Buffer_Tx, BufferSize);
    
        /* TransferStatus = PASSED, if the transmitted and received data
        /* TransferStatus = FAILED, if the transmitted and received data
        
        
    {
    }



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* PCLK2 = HCLK/2 */ 
        RCC_PCLK2Config (RCC_HCLK_Div2);
    
        /* Enable peripheral clocks -------------------------------------------------- */ 
#ifdef USE_STM3210C_EVAL
        /* Enable GPIO clock for SPI_MASTER and SPI_SLAVE */ 
        RCC_APB2PeriphClockCmd (SPI_MASTER_GPIO_CLK | SPI_SLAVE_GPIO_CLK | 
    
        /* Enable SPI_MASTER Periph clock */ 
        RCC_APB1PeriphClockCmd (SPI_MASTER_CLK, ENABLE);
    
#else /* 
        /* Enable SPI_MASTER clock and GPIO clock for SPI_MASTER and SPI_SLAVE */ 
        RCC_APB2PeriphClockCmd (SPI_MASTER_GPIO_CLK | SPI_SLAVE_GPIO_CLK | 
    
#endif /* 
        /* Enable SPI_SLAVE Periph clock */ 
        RCC_APB1PeriphClockCmd (SPI_SLAVE_CLK, ENABLE);


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
#ifdef USE_STM3210C_EVAL
        /* Enable SPI3 Pins Software Remapping */ 
        GPIO_PinRemapConfig (GPIO_Remap_SPI3, ENABLE);
    
#endif /* 
        
        /* Configure SPI_MASTER pins: SCK, MISO and MOSI */ 
        GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_SCK | SPI_MASTER_PIN_MISO | SPI_MASTER_PIN_MOSI;
    
    
    
    
        /* Configure SPI_SLAVE pins: SCK, MISO and MOSI */ 
        GPIO_InitStructure.GPIO_Pin = SPI_SLAVE_PIN_SCK | SPI_SLAVE_PIN_MISO | SPI_SLAVE_PIN_MOSI;
    


/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* 1 bit for pre-emption priority, 3 bits for subpriority */ 
        NVIC_PriorityGroupConfig (NVIC_PriorityGroup_1);
    
        /* Configure and enable SPI_MASTER interrupt ------------------------------- */ 
        NVIC_InitStructure.NVIC_IRQChannel = SPI_MASTER_IRQn;
    
    
    
    
    
        /* Configure and enable SPI_SLAVE interrupt -------------------------------- */ 
        NVIC_InitStructure.NVIC_IRQChannel = SPI_SLAVE_IRQn;
    
    
    


/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *   FAILED: pBuffer1 differs from pBuffer2
  */ 
    TestStatus Buffercmp (uint8_t * pBuffer1, uint8_t * pBuffer2, uint16_t BufferLength) 
{
    
        
    {
        
            
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
    }



#endif /* 
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 