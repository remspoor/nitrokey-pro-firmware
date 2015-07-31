/**
  ******************************************************************************
  * @file I2S/SPI_I2S_Switch/main.c 
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
    
    /* Local includes ------------------------------------------------------------ */ 
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup I2S_SPI_I2S_Switch
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
#define BufferSize   32
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    I2S_InitTypeDef I2S_InitStructure;


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
    
        /* I2S peripheral configuration */ 
        I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
    
    
    
    
    
        /* I2S3 Master Transmitter to I2S2 Slave Receiver communication ------------ */ 
        /* I2S3 configuration */ 
        I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;
    
    
        /* I2S2 configuration */ 
        I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveRx;
    
    
        /* Enable the I2S2 */ 
        I2S_Cmd (SPI2, ENABLE);
    
        /* Enable the I2S3 */ 
        I2S_Cmd (SPI3, ENABLE);
    
        /* Begin the communication in I2S mode */ 
        while (RxIdx < BufferSize)
        
    {
        
            /* Wait the Tx buffer to be empty */ 
            while (SPI_I2S_GetFlagStatus (SPI3, SPI_I2S_FLAG_TXE) == RESET)
            
        {
        }
        
            /* Send a data from I2S3 */ 
            SPI_I2S_SendData (SPI3, I2S3_Buffer_Tx[TxIdx++]);
        
            /* Wait the Rx buffer to be full */ 
            while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_RXNE) == RESET)
            
        {
        }
        
            /* Store the I2S2 received data in the relative data table */ 
            I2S2_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData (SPI2);
    
    
    
        /* TransferStatus1 = PASSED, if the data transmitted from I2S3 and received by
           transmitted from I2S3 and received by
        
        /* Reset TxIdx, RxIdx indexes */ 
        TxIdx = 0;
    
    
        /* Switch to SPI mode communication ---------------------------------------- */ 
        /* SPI3 configuration */ 
        SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    
    
    
    
    
    
    
    
    
    
        /* SPI2 configuration ------------------------------------------------------ */ 
        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_RxOnly;
    
    
    
        /* Enable SPI2 */ 
        SPI_Cmd (SPI2, ENABLE);
    
        /* Enable SPI3 */ 
        SPI_Cmd (SPI3, ENABLE);
    
        /* Begin the communication in SPI mode */ 
        while (RxIdx < BufferSize)
        
    {
        
            /* Wait the Tx buffer to be empty */ 
            while (SPI_I2S_GetFlagStatus (SPI3, SPI_I2S_FLAG_TXE) == RESET)
            
        {
        }
        
            /* Send a data from SPI3 */ 
            SPI_I2S_SendData (SPI3, SPI3_Buffer_Tx[TxIdx++]);
        
            /* Wait the Rx buffer to be full */ 
            while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_RXNE) == RESET)
            
        {
        }
        
            /* Store the SPI2 received data in the relative data table */ 
            SPI2_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData (SPI2);
    
    
    
        /* TransferStatus2 = PASSED, if the data transmitted from SPI3 and received by
           transmitted from SPI3 and received by
        
        /* Reset TxIdx, RxIdx indexes and receive table values */ 
        for (TxIdx = 0; TxIdx < BufferSize; TxIdx++)
        
    {
        
    
    
    
    
        /* I2S3 Slave Transmitter to I2S2 Master Receiver communication ------------ */ 
        /* I2S3 configuration */ 
        I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveTx;
    
    
        /* I2S2 configuration */ 
        I2S_InitStructure.I2S_Mode = I2S_Mode_MasterRx;
    
    
        /* Wait the Tx buffer to be empty */ 
        while (SPI_I2S_GetFlagStatus (SPI3, SPI_I2S_FLAG_TXE) == RESET)
        
    {
    }
    
        /* Prepare the first data to be sent from the slave */ 
        SPI_I2S_SendData (SPI3, I2S3_Buffer_Tx[TxIdx++]);
    
        /* Enable the I2S3 */ 
        I2S_Cmd (SPI3, ENABLE);
    
        /* Enable the I2S2 */ 
        I2S_Cmd (SPI2, ENABLE);
    
        /* Begin the communication in I2S mode */ 
        while (RxIdx < BufferSize)
        
    {
        
            /* Wait the Rx buffer to be full */ 
            while (SPI_I2S_GetFlagStatus (SPI2, SPI_I2S_FLAG_RXNE) == RESET)
            
        {
        }
        
            /* Store the I2S2 received data in the relative data table */ 
            I2S2_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData (SPI2);
        
            /* Wait the Tx buffer to be empty */ 
            while (SPI_I2S_GetFlagStatus (SPI3, SPI_I2S_FLAG_TXE) == RESET)
            
        {
        }
        
            /* Send a data from I2S3 */ 
            SPI_I2S_SendData (SPI3, I2S3_Buffer_Tx[TxIdx++]);
    
    
    
        /* TransferStatus3 = PASSED, if the data transmitted from I2S3 and received by
           transmitted from I2S3 and received by
        
        
    {
    }



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* RCC system reset(for debug purpose) */ 
        RCC_DeInit ();
    
        /* Enable HSE */ 
        RCC_HSEConfig (RCC_HSE_ON);
    
        /* Wait till HSE is ready */ 
        HSEStartUpStatus = RCC_WaitForHSEStartUp ();
    
        
    {
        
            /* Enable Prefetch Buffer */ 
            FLASH_PrefetchBufferCmd (FLASH_PrefetchBuffer_Enable);
        
            /* Flash 2 wait state */ 
            FLASH_SetLatency (FLASH_Latency_2);
        
            /* HCLK = SYSCLK */ 
            RCC_HCLKConfig (RCC_SYSCLK_Div1);
        
            /* PCLK2 = HCLK */ 
            RCC_PCLK2Config (RCC_HCLK_Div1);
        
            /* PCLK1 = HCLK/2 */ 
            RCC_PCLK1Config (RCC_HCLK_Div2);
        
            /* ADCCLK = PCLK2/4 */ 
            RCC_ADCCLKConfig (RCC_PCLK2_Div4);
        
#ifndef STM32F10X_CL  
            /* PLLCLK = 8MHz * 9 = 72 MHz */ 
            RCC_PLLConfig (RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        
#else /* 
            /* Configure PLLs ******************************************************** */ 
            /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz */ 
            RCC_PREDIV2Config (RCC_PREDIV2_Div5);
        
        
            /* Enable PLL2 */ 
            RCC_PLL2Cmd (ENABLE);
        
            /* Wait till PLL2 is ready */ 
            while (RCC_GetFlagStatus (RCC_FLAG_PLL2RDY) == RESET)
            
        {
        }
        
            /* PLL configuration: PLLCLK = (PLL2 / 5) * 9 = 72 MHz */ 
            RCC_PREDIV1Config (RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
        
        
            /* PPL3 configuration: PLL3CLK = (HSE / 5) * 11 = PLL3_VCO = 110 MHz */ 
            RCC_PLL3Config (RCC_PLL3Mul_11);
        
            /* Enable PLL3 */ 
            RCC_PLL3Cmd (ENABLE);
        
            /* Wait till PLL3 is ready */ 
            while (RCC_GetFlagStatus (RCC_FLAG_PLL3RDY) == RESET)
            
        {
        }
        
            /* Configure I2S clock source: On Connectivity-Line Devices, the I2S can be 
               guarantee higher 
            RCC_I2S3CLKConfig (RCC_I2S3CLKSource_PLL3_VCO);
        
        
#endif /* 
            
            /* Enable PLL */ 
            RCC_PLLCmd (ENABLE);
        
            /* Wait till PLL is ready */ 
            while (RCC_GetFlagStatus (RCC_FLAG_PLLRDY) == RESET)
            
        {
        
        
            /* Select PLL as system clock source */ 
            RCC_SYSCLKConfig (RCC_SYSCLKSource_PLLCLK);
        
            /* Wait till PLL is used as system clock source */ 
            while (RCC_GetSYSCLKSource () != 0x08)
            
        {
        
    
    
        /* Enable peripheral clocks -------------------------------------------------- */ 
        /* GPIOA, GPIOB and AFIO clocks enable */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | 
    
#ifdef USE_STM3210C_EVAL 
        /* GPIOC Clock enable (for the SPI3 remapped pins) */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE);
    
#endif  /* USE_STM3210C_EVAL */  
        
        /* SPI2 and SPI3 clocks enable */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_SPI2 | RCC_APB1Periph_SPI3, ENABLE);



/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
#ifdef USE_STM3210E_EVAL
        /* Disable the JTAG interface and enable the SWJ interface
           can be remapped on other GPIO pins */ 
        GPIO_PinRemapConfig (GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    
#endif  /* USE_STM3210E_EVAL */ 
        
        /* Configure SPI2 pins: CK, WS and SD --------------------------------- */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
    
    
    
    
#ifdef USE_STM3210C_EVAL
        
        /* Remap SPI3 on PC10-PC11-PC12-PA4 GPIO pins ------------------------ */ 
        GPIO_PinRemapConfig (GPIO_Remap_SPI3, ENABLE);
    
        /* Configure SPI3 pins: CK and SD ------------------------------------ */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12;
    
    
        /* Configure SPI3 pins: WS ------------------------------------------- */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    
    
#elif defined (USE_STM3210E_EVAL)
        
        /* Configure SPI3 pins: CK and SD ------------------------------------ */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
    
    
        /* Configure SPI3 pins: WS ------------------------------------------- */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    
    
#endif  /* USE_STM3210C_EVAL */ 
} 

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