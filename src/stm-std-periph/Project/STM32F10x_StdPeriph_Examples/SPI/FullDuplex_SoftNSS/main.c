/**
  ******************************************************************************
  * @file    SPI/FullDuplex_SoftNSS/main.c 
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
    
/** @addtogroup SPI_FullDuplex_SoftNSS
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
0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
        0x0D, 0x0E, 

{
0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 
        0x5D, 0x5E, 







    /* Private functions --------------------------------------------------------- */ 
void RCC_Configuration (void);





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
    
        /* GPIO configuration ------------------------------------------------------ */ 
        GPIO_Configuration ();
    
        /* 1st phase: SPIy Master and SPIz Slave */ 
        /* SPIy Config ------------------------------------------------------------- */ 
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    
    
    
    
    
    
    
    
    
    
        /* SPIz Config ------------------------------------------------------------- */ 
        SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    
    
        /* Enable SPIy */ 
        SPI_Cmd (SPIy, ENABLE);
    
        /* Enable SPIz */ 
        SPI_Cmd (SPIz, ENABLE);
    
        /* Transfer procedure */ 
        while (TxIdx < BufferSize)
        
    {
        
            /* Wait for SPIy Tx buffer empty */ 
            while (SPI_I2S_GetFlagStatus (SPIy, SPI_I2S_FLAG_TXE) == RESET);
        
            /* Send SPIz data */ 
            SPI_I2S_SendData (SPIz, SPIz_Buffer_Tx[TxIdx]);
        
            /* Send SPIy data */ 
            SPI_I2S_SendData (SPIy, SPIy_Buffer_Tx[TxIdx++]);
        
            /* Wait for SPIz data reception */ 
            while (SPI_I2S_GetFlagStatus (SPIz, SPI_I2S_FLAG_RXNE) == RESET);
        
            /* Read SPIz received data */ 
            SPIz_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData (SPIz);
        
            /* Wait for SPIy data reception */ 
            while (SPI_I2S_GetFlagStatus (SPIy, SPI_I2S_FLAG_RXNE) == RESET);
        
            /* Read SPIy received data */ 
            SPIy_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData (SPIy);
    
    
        /* Check the corectness of written dada */ 
        TransferStatus1 = Buffercmp (SPIz_Buffer_Rx, SPIy_Buffer_Tx, BufferSize);
    
    
        /* TransferStatus1, TransferStatus2 = PASSED, if the transmitted and received data
        /* TransferStatus1, TransferStatus2 = FAILED, if the transmitted and received data
        
        /* 2nd phase: SPIy Slave and SPIz Master */ 
        /* SPIy Re-configuration --------------------------------------------------- */ 
        SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    
    
        /* SPIz Re-configuration --------------------------------------------------- */ 
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    
    
        /* Reset TxIdx, RxIdx indexes and receive tables values */ 
        TxIdx = 0;
    
    
        SPIz_Buffer_Rx[k] = 0;
    
        SPIy_Buffer_Rx[k] = 0;
    
        /* Transfer procedure */ 
        while (TxIdx < BufferSize)
        
    {
        
            /* Wait for SPIz Tx buffer empty */ 
            while (SPI_I2S_GetFlagStatus (SPIz, SPI_I2S_FLAG_TXE) == RESET);
        
            /* Send SPIy data */ 
            SPI_I2S_SendData (SPIy, SPIy_Buffer_Tx[TxIdx]);
        
            /* Send SPIz data */ 
            SPI_I2S_SendData (SPIz, SPIz_Buffer_Tx[TxIdx++]);
        
            /* Wait for SPIy data reception */ 
            while (SPI_I2S_GetFlagStatus (SPIy, SPI_I2S_FLAG_RXNE) == RESET);
        
            /* Read SPIy received data */ 
            SPIy_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData (SPIy);
        
            /* Wait for SPIz data reception */ 
            while (SPI_I2S_GetFlagStatus (SPIz, SPI_I2S_FLAG_RXNE) == RESET);
        
            /* Read SPIz received data */ 
            SPIz_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData (SPIz);
    
    
        /* Check the corectness of written dada */ 
        TransferStatus3 = Buffercmp (SPIz_Buffer_Rx, SPIy_Buffer_Tx, BufferSize);
    
    
        /* TransferStatus3, TransferStatus4 = PASSED, if the transmitted and received data
        /* TransferStatus3, TransferStatus4 = FAILED, if the transmitted and received data
        
        
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
        /* Enable GPIO clock for SPIy and SPIz */ 
        RCC_APB2PeriphClockCmd (SPIy_GPIO_CLK | SPIz_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
    
        /* Enable SPIy Periph clock */ 
        RCC_APB1PeriphClockCmd (SPIy_CLK, ENABLE);
    
#else /* 
        /* Enable SPIy clock and GPIO clock for SPIy and SPIz */ 
        RCC_APB2PeriphClockCmd (SPIy_GPIO_CLK | SPIz_GPIO_CLK | SPIy_CLK, ENABLE);
    
#endif /* 
        /* Enable SPIz Periph clock */ 
        RCC_APB1PeriphClockCmd (SPIz_CLK, ENABLE);


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
        
        /* Configure SPIy pins: SCK, MISO and MOSI */ 
        GPIO_InitStructure.GPIO_Pin = SPIy_PIN_SCK | SPIy_PIN_MISO | SPIy_PIN_MOSI;
    
    
    
    
        /* Configure SPIz pins: SCK, MISO and MOSI */ 
        GPIO_InitStructure.GPIO_Pin = SPIz_PIN_SCK | SPIz_PIN_MISO | SPIz_PIN_MOSI;
    


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