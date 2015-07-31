/**
  ******************************************************************************
  * @file    SPI/CRC/main.c 
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
    
/** @addtogroup SPI_CRC
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
#define BufferSize  32
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    SPI_InitTypeDef SPI_InitStructure;

{
0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C, 
        0x1314, 0x1516, 0x1718, 
        0x2324, 

{
0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C, 
        0x6364, 0x6566, 0x6768, 
        0x7374, 






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
    
        /* GPIO configuration ------------------------------------------------------ */ 
        GPIO_Configuration ();
    
        /* SPI1 configuration ------------------------------------------------------ */ 
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    
    
    
    
    
    
    
    
    
    
        /* SPI2 configuration ------------------------------------------------------ */ 
        SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    
    
        /* Enable SPI1 CRC calculation */ 
        SPI_CalculateCRC (SPI1, ENABLE);
    
        /* Enable SPI2 CRC calculation */ 
        SPI_CalculateCRC (SPI2, ENABLE);
    
        /* Enable SPI1 */ 
        SPI_Cmd (SPI1, ENABLE);
    
        /* Enable SPI2 */ 
        SPI_Cmd (SPI2, ENABLE);
    
        /* Transfer procedure */ 
        while (TxIdx < BufferSize - 1)
        
    {
        
            /* Wait for SPI1 Tx buffer empty */ 
            while (SPI_I2S_GetFlagStatus (SPI1, SPI_I2S_FLAG_TXE) == RESET);
        
            /* Send SPI2 data */ 
            SPI_I2S_SendData (SPI2, SPI2_Buffer_Tx[TxIdx]);
        
            /* Send SPI1 data */ 
            SPI_I2S_SendData (SPI1, SPI1_Buffer_Tx[TxIdx++]);
        
            /* Wait for SPI2 data reception */ 
            while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_RXNE) == RESET);
        
            /* Read SPI2 received data */ 
            SPI2_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData (SPI2);
        
            /* Wait for SPI1 data reception */ 
            while (SPI_I2S_GetFlagStatus (SPI1, SPI_I2S_FLAG_RXNE) == RESET);
        
            /* Read SPI1 received data */ 
            SPI1_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData (SPI1);
    
    
        /* Wait for SPI1 Tx buffer empty */ 
        while (SPI_I2S_GetFlagStatus (SPI1, SPI_I2S_FLAG_TXE) == RESET);
    
        /* Wait for SPI2 Tx buffer empty */ 
        while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_TXE) == RESET);
    
        /* Send last SPI2_Buffer_Tx data */ 
        SPI_I2S_SendData (SPI2, SPI2_Buffer_Tx[TxIdx]);
    
        /* Enable SPI2 CRC transmission */ 
        SPI_TransmitCRC (SPI2);
    
        /* Send last SPI1_Buffer_Tx data */ 
        SPI_I2S_SendData (SPI1, SPI1_Buffer_Tx[TxIdx]);
    
        /* Enable SPI1 CRC transmission */ 
        SPI_TransmitCRC (SPI1);
    
        /* Wait for SPI1 last data reception */ 
        while (SPI_I2S_GetFlagStatus (SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    
        /* Read SPI1 last received data */ 
        SPI1_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData (SPI1);
    
        /* Wait for SPI2 last data reception */ 
        while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_RXNE) == RESET);
    
        /* Read SPI2 last received data */ 
        SPI2_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData (SPI2);
    
        /* Wait for SPI1 data reception: CRC transmitted by SPI2 */ 
        while (SPI_I2S_GetFlagStatus (SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    
        /* Wait for SPI2 data reception: CRC transmitted by SPI1 */ 
        while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_RXNE) == RESET);
    
        /* Check the received data with the send ones */ 
        TransferStatus1 = Buffercmp (SPI2_Buffer_Rx, SPI1_Buffer_Tx, BufferSize);
    
    
        /* TransferStatus1, TransferStatus2 = PASSED, if the data transmitted and received
        /* TransferStatus1, TransferStatus2 = FAILED, if the data transmitted and received
        
        /* Test on the SPI1 CRC Error flag */ 
        if ((SPI_I2S_GetFlagStatus (SPI1, SPI_FLAG_CRCERR)) == SET)
        
    {
        
    
    
        /* Test on the SPI2 CRC Error flag */ 
        if ((SPI_I2S_GetFlagStatus (SPI2, SPI_FLAG_CRCERR)) == SET)
        
    {
        
    
    
        /* Read SPI1 received CRC value */ 
        CRC1Value = SPI_I2S_ReceiveData (SPI1);
    
        /* Read SPI2 received CRC value */ 
        CRC2Value = SPI_I2S_ReceiveData (SPI2);
    
        
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
        /* GPIOA, GPIOB and SPI1 clock enable */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | 
    
        /* SPI2 Periph clock enable */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_SPI2, ENABLE);


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
        /* Configure SPI1 pins: SCK, MISO and MOSI --------------------------------- */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    
    
    
    
        /* Configure SPI2 pins: SCK, MISO and MOSI --------------------------------- */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    


/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *   FAILED: pBuffer1 differs from pBuffer2
  */ 
    TestStatus Buffercmp (uint16_t * pBuffer1, uint16_t * pBuffer2, uint16_t BufferLength) 
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