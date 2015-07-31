/**
  ******************************************************************************
  * @file    SDIO/main.c 
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
#include "stm32_eval_sdio_sd.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup SDIO_Example
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
#define BLOCK_SIZE            512 /* Block Size in Bytes */
    
#define NUMBER_OF_BLOCKS      2  /* For Multi Blocks operation (Read/Write) */
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    SD_CardInfo SDCardInfo;





    /* Private function prototypes ----------------------------------------------- */ 
void NVIC_Configuration (void);






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
        
        /* Interrupt Config */ 
        NVIC_Configuration ();
    
  /*-------------------------- SD Init ----------------------------- */ 
        Status = SD_Init ();
    
  /*------------------- Block Erase -------------------------------*/ 
        if (Status == SD_OK)
        
    {
        
            /* Erase NumberOfBlocks Blocks of WRITE_BL_LEN(512 Bytes) */ 
            Status = SD_Erase (0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));
    
    
        
    {
        
    
    
        
    {
        
    
    
  /*------------------- Block Read/Write --------------------------*/ 
        /* Fill the buffer to send */ 
        Fill_Buffer (Buffer_Block_Tx, BLOCK_SIZE, 0xFFFF);
    
        
    {
        
            /* Write block of 512 bytes on address 0 */ 
            Status = SD_WriteBlock (Buffer_Block_Tx, 0x00, BLOCK_SIZE);
    
    
        
    {
        
            /* Read block of 512 bytes from address 0 */ 
            Status = SD_ReadBlock (Buffer_Block_Rx, 0x00, BLOCK_SIZE);
    
    
        
    {
        
            /* Check the corectness of written dada */ 
            TransferStatus1 = Buffercmp (Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE);
    
    
  /*--------------- Multiple Block Read/Write ---------------------*/ 
        /* Fill the buffer to send */ 
        Fill_Buffer (Buffer_MultiBlock_Tx, MULTI_BUFFER_SIZE, 0x0);
    
        
    {
        
            /* Write multiple block of many bytes on address 0 */ 
            Status = SD_WriteMultiBlocks (Buffer_MultiBlock_Tx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
    
    
        
    {
        
            /* Read block of many bytes from address 0 */ 
            Status = SD_ReadMultiBlocks (Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
    
    
        
    {
        
            /* Check the corectness of written dada */ 
            TransferStatus2 = Buffercmp (Buffer_MultiBlock_Tx, Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);
    
    
        /* Infinite loop */ 
        while (1)
        
    {
    }



/**
  * @brief  Configures SDIO IRQ channel.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* Configure the NVIC Preemption Priority Bits */ 
        NVIC_PriorityGroupConfig (NVIC_PriorityGroup_1);
    
    
    
    
    


/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */ 
    TestStatus Buffercmp (uint8_t * pBuffer1, uint8_t * pBuffer2, uint32_t BufferLength) 
{
    
        
    {
        
            
        {
            
        
        
        
    
    



/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the Buffer to fill
  * @param  BufferLength: size of the buffer to fill
  * @param  Offset: first value to fill on the Buffer
  * @retval None
  */ 
void Fill_Buffer (uint8_t * pBuffer, uint32_t BufferLength, uint32_t Offset) 
{
    
    
        /* Put in global buffer same values */ 
        for (index = 0; index < BufferLength; index++)
        
    {
        
    



/**
  * @brief  Checks if a buffer has all its values are equal to zero.
  * @param  pBuffer: buffer to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer values are zero
  *         FAILED: At least one value from pBuffer buffer is diffrent from zero.
  */ 
    TestStatus eBuffercmp (uint8_t * pBuffer, uint32_t BufferLength) 
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