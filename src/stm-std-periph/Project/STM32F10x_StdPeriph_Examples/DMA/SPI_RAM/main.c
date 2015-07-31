/**
  ******************************************************************************
  * @file    DMA/SPI_RAM/main.c 
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
    
/** @addtogroup DMA_SPI_RAM
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
#define BufferSize         32
#define CRCPolynomial      7
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    SPI_InitTypeDef SPI_InitStructure;







{
0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
        0x0D, 0x0E, 0x0F, 0x10, 

{
0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 
        0x5D, 0x5E, 0x5F, 0x60, 

    /* Private function prototypes ----------------------------------------------- */ 
void RCC_Configuration (void);





    /* Private functions --------------------------------------------------------- */ 
    
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
        
        /* System Clocks Configuration */ 
        RCC_Configuration ();
    
        /* Configure the GPIO ports */ 
        GPIO_Configuration ();
    
        /* SPI_MASTER configuration ------------------------------------------------ */ 
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    
    
    
    
    
    
    
    
    
    
        /* SPI_SLAVE configuration ------------------------------------------------------ */ 
        SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    
    
        /* SPI_MASTER_Rx_DMA_Channel configuration --------------------------------- */ 
        DMA_DeInit (SPI_MASTER_Rx_DMA_Channel);
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* SPI_MASTER_Tx_DMA_Channel configuration --------------------------------- */ 
        DMA_DeInit (SPI_MASTER_Tx_DMA_Channel);
    
    
    
    
    
    
        /* SPI_SLAVE_Rx_DMA_Channel configuration ---------------------------------- */ 
        DMA_DeInit (SPI_SLAVE_Rx_DMA_Channel);
    
    
    
    
    
    
        /* SPI_SLAVE_Tx_DMA_Channel configuration ---------------------------------- */ 
        DMA_DeInit (SPI_SLAVE_Tx_DMA_Channel);
    
    
    
    
    
    
        /* Enable SPI_MASTER DMA Tx request */ 
        SPI_I2S_DMACmd (SPI_MASTER, SPI_I2S_DMAReq_Tx, ENABLE);
    
        /* Enable SPI_MASTER DMA Rx request */ 
        SPI_I2S_DMACmd (SPI_MASTER, SPI_I2S_DMAReq_Rx, ENABLE);
    
        /* Enable SPI_SLAVE DMA Tx request */ 
        SPI_I2S_DMACmd (SPI_SLAVE, SPI_I2S_DMAReq_Tx, ENABLE);
    
        /* Enable SPI_SLAVE DMA Rx request */ 
        SPI_I2S_DMACmd (SPI_SLAVE, SPI_I2S_DMAReq_Rx, ENABLE);
    
        /* Enable SPI_MASTER CRC calculation */ 
        SPI_CalculateCRC (SPI_MASTER, ENABLE);
    
        /* Enable SPI_SLAVE CRC calculation */ 
        SPI_CalculateCRC (SPI_SLAVE, ENABLE);
    
        /* Enable SPI_SLAVE */ 
        SPI_Cmd (SPI_SLAVE, ENABLE);
    
        /* Enable SPI_MASTER */ 
        SPI_Cmd (SPI_MASTER, ENABLE);
    
        /* Enable DMA channels */ 
        DMA_Cmd (SPI_MASTER_Rx_DMA_Channel, ENABLE);
    
    
    
    
        /* Transfer complete */ 
        while (!DMA_GetFlagStatus (SPI_MASTER_Rx_DMA_FLAG));
    
    
    
    
        /* Wait for SPI_MASTER data reception: CRC transmitted by SPI_SLAVE */ 
        while (SPI_I2S_GetFlagStatus (SPI_MASTER, SPI_I2S_FLAG_RXNE) == RESET);
    
        /* Wait for SPI_SLAVE data reception: CRC transmitted by SPI_MASTER */ 
        while (SPI_I2S_GetFlagStatus (SPI_SLAVE, SPI_I2S_FLAG_RXNE) == RESET);
    
        /* Check the corectness of written dada */ 
        TransferStatus1 = Buffercmp (SPI_SLAVE_Buffer_Rx, SPI_MASTER_Buffer_Tx, BufferSize);
    
    
        /* TransferStatus1, TransferStatus2 = PASSED, if the data transmitted and received 
        /* TransferStatus1, TransferStatus2 = FAILED, if the data transmitted and received 
        
        /* Test on the SPI_MASTER CRCR ERROR flag */ 
        if ((SPI_I2S_GetFlagStatus (SPI_MASTER, SPI_FLAG_CRCERR)) != RESET)
        
    {
        
    
    
        /* Test on the SPI_SLAVE CRCR ERROR flag */ 
        if ((SPI_I2S_GetFlagStatus (SPI_SLAVE, SPI_FLAG_CRCERR)) != RESET)
        
    {
        
    
    
        /* Read SPI_MASTER received CRC value */ 
        SPI_MASTERCRCValue = SPI_I2S_ReceiveData (SPI_MASTER);
    
        /* Read SPI_SLAVE received CRC value */ 
        SPI_SLAVECRCValue = SPI_I2S_ReceiveData (SPI_SLAVE);
    
        
    {
    



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* PCLK2 = HCLK/2 */ 
        RCC_PCLK2Config (RCC_HCLK_Div2);
    
        /* Enable peripheral clocks ------------------------------------------------ */ 
        /* Enable DMA1 or/and DMA2 clock */ 
        RCC_AHBPeriphClockCmd (SPI_MASTER_DMA_CLK | SPI_SLAVE_DMA_CLK, ENABLE);
    
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
  * @brief  Compares two buffers.
  * @param  pBuffer, pBuffer1: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer identical to pBuffer1
  *   FAILED: pBuffer differs from pBuffer1
  */ 
    TestStatus Buffercmp (uint8_t * pBuffer, uint8_t * pBuffer1, uint16_t BufferLength) 
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
    



#endif /* 
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 