/**
  ******************************************************************************
  * @file DMA/I2C_RAM/main.c 
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
    
/** @addtogroup DMA_I2C_RAM
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
#define I2C1_DR_Address        0x40005410
#define I2C2_DR_Address        0x40005810
#define I2C1_SLAVE_ADDRESS7    0x30
#define I2C2_SLAVE_ADDRESS7    0x30
#define BufferSize             8
#define ClockSpeed             100000
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    I2C_InitTypeDef I2C_InitStructure;


{
1, 2, 3, 4, 5, 6, 7, 8};






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
        
        /* System Clocks Configuration */ 
        RCC_Configuration ();
    
        /* Configure the GPIO ports */ 
        GPIO_Configuration ();
    
        /* DMA1 channel5 configuration ---------------------------------------------- */ 
        DMA_DeInit (DMA1_Channel5);
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* DMA1 channel6 configuration ---------------------------------------------- */ 
        DMA_DeInit (DMA1_Channel6);
    
    
    
    
    
    
        /* Enable I2C1 and I2C2 ---------------------------------------------------- */ 
        I2C_Cmd (I2C1, ENABLE);
    
    
        /* I2C1 configuration ------------------------------------------------------ */ 
        I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    
    
    
    
    
    
    
        /* I2C2 configuration ------------------------------------------------------ */ 
        I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE_ADDRESS7;
    
    
  /*----- Transmission Phase -----*/ 
        /* Send I2C1 START condition */ 
        I2C_GenerateSTART (I2C1, ENABLE);
    
        /* Test on I2C1 EV5 and clear it */ 
        while (!I2C_CheckEvent (I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    
        /* Send I2C2 slave Address for write */ 
        I2C_Send7bitAddress (I2C1, I2C2_SLAVE_ADDRESS7, I2C_Direction_Transmitter);
    
        /* Test on I2C2 EV1 and clear it */ 
        while (!I2C_CheckEvent (I2C2, I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED));
    
        /* Test on I2C1 EV6 and clear it */ 
        while (!I2C_CheckEvent (I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
        /* Enable I2C2 DMA */ 
        I2C_DMACmd (I2C2, ENABLE);
    
        /* Enable I2C1 DMA */ 
        I2C_DMACmd (I2C1, ENABLE);
    
        /* Enable DMA1 Channel5 */ 
        DMA_Cmd (DMA1_Channel5, ENABLE);
    
        /* Enable DMA1 Channel6 */ 
        DMA_Cmd (DMA1_Channel6, ENABLE);
    
        /* DMA1 Channel5 transfer complete test */ 
        while (!DMA_GetFlagStatus (DMA1_FLAG_TC5));
    
        /* DMA1 Channel6 transfer complete test */ 
        while (!DMA_GetFlagStatus (DMA1_FLAG_TC6));
    
        /* Send I2C1 STOP Condition */ 
        I2C_GenerateSTOP (I2C1, ENABLE);
    
        /* Test on I2C2 EV4 */ 
        while (!I2C_CheckEvent (I2C2, I2C_EVENT_SLAVE_STOP_DETECTED));
    
        /* Clear I2C2 STOPF flag: read operation to I2C_SR1 followed by a 
        (void) (I2C_GetFlagStatus (I2C2, I2C_FLAG_STOPF));
    
    
        /* Check if the transmitted and received data are equal */ 
        TransferStatus = Buffercmp (I2C1_Buffer_Tx, I2C2_Buffer_Rx, BufferSize);
    
        /* TransferStatus = PASSED, if the transmitted and received data 
        /* TransferStatus = FAILED, if the transmitted and received data 
        
        
    {
    



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* Enable DMA1 clock */ 
        RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1, ENABLE);
    
        /* Enable GPIOB clock */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
    
        /* Enable I2C1 and I2C2 clock */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2, ENABLE);


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
        /* Configure I2C1 pins: SCL and SDA */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    
    
    
    
        /* Configure I2C2 pins: SCL and SDA */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    


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