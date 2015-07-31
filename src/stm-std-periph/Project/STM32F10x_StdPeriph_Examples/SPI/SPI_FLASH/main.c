/**
  ******************************************************************************
  * @file    SPI/SPI_FLASH/main.c 
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
#include "stm32_eval.h"
#include "stm32_eval_spi_flash.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup SPI_FLASH
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
#define  FLASH_WriteAddress     0x700000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress
    
#if defined(USE_STM32100B_EVAL)
#define  sFLASH_ID       sFLASH_M25P128_ID
#else /* 
#define  sFLASH_ID       sFLASH_M25P64_ID
#endif /* 
    
#define  BufferSize (countof(Tx_Buffer)-1)
    
    /* Private macro ------------------------------------------------------------- */ 
#define countof(a) (sizeof(a) / sizeof(*(a)))
    
    /* Private variables --------------------------------------------------------- */ 
    uint8_t Tx_Buffer[] = "STM32F10x SPI Firmware Library Example: communication with an M25P SPI FLASH";





    /* Private functions --------------------------------------------------------- */ 
    TestStatus Buffercmp (uint8_t * pBuffer1, uint8_t * pBuffer2, uint16_t BufferLength);

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
        
        /* Initialize Leds mounted on STM3210X-EVAL board */ 
        STM_EVAL_LEDInit (LED1);
    
    
        /* Initialize the SPI FLASH driver */ 
        sFLASH_Init ();
    
        /* Get SPI Flash ID */ 
        FlashID = sFLASH_ReadID ();
    
        /* Check the SPI Flash ID */ 
        if (FlashID == sFLASH_ID)
        
    {
        
            /* OK: Turn on LD1 */ 
            STM_EVAL_LEDOn (LED1);
        
            /* Perform a write in the Flash followed by a read of the written data */ 
            /* Erase SPI FLASH Sector to write on */ 
            sFLASH_EraseSector (FLASH_SectorToErase);
        
            /* Write Tx_Buffer data to SPI FLASH memory */ 
            sFLASH_WriteBuffer (Tx_Buffer, FLASH_WriteAddress, BufferSize);
        
            /* Read data from SPI FLASH memory */ 
            sFLASH_ReadBuffer (Rx_Buffer, FLASH_ReadAddress, BufferSize);
        
            /* Check the corectness of written dada */ 
            TransferStatus1 = Buffercmp (Tx_Buffer, Rx_Buffer, BufferSize);
        
            /* TransferStatus1 = PASSED, if the transmitted and received data by SPI1
            /* TransferStatus1 = FAILED, if the transmitted and received data by SPI1
            
            /* Perform an erase in the Flash followed by a read of the written data */ 
            /* Erase SPI FLASH Sector to write on */ 
            sFLASH_EraseSector (FLASH_SectorToErase);
        
            /* Read data from SPI FLASH memory */ 
            sFLASH_ReadBuffer (Rx_Buffer, FLASH_ReadAddress, BufferSize);
        
            /* Check the corectness of erasing operation dada */ 
            for (Index = 0; Index < BufferSize; Index++)
            
        {
            
                
            {
                
            
        
        
            /* TransferStatus2 = PASSED, if the specified sector part is erased */ 
            /* TransferStatus2 = FAILED, if the specified sector part is not well erased */ 
    }
    
    else
        
    {
        
            /* Error: Turn on LD2 */ 
            STM_EVAL_LEDOn (LED2);
    
    
        
    {
    }



/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
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