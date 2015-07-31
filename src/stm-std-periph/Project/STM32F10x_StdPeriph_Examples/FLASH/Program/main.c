/**
  ******************************************************************************
  * @file    FLASH/Program/main.c 
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
    
/** @addtogroup FLASH_Program
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
    /* Define the STM32F10x FLASH Page Size depending on the used STM32 device */ 
#if defined (STM32F10X_HD) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
#define FLASH_PAGE_SIZE    ((uint16_t)0x800)
#else /* 
#define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#endif /* 
    
#define BANK1_WRITE_START_ADDR  ((uint32_t)0x08008000)
#define BANK1_WRITE_END_ADDR    ((uint32_t)0x0800C000)
    
#ifdef STM32F10X_XL
#define BANK2_WRITE_START_ADDR   ((uint32_t)0x08088000)
#define BANK2_WRITE_END_ADDR     ((uint32_t)0x0808C000)
#endif  /* STM32F10X_XL */
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    uint32_t EraseCounter = 0x00, Address = 0x00;







#ifdef STM32F10X_XL
volatile TestStatus MemoryProgramStatus2 = PASSED;


#endif  /* STM32F10X_XL */
    
    /* Private function prototypes ----------------------------------------------- */ 
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
        
        /* Porgram FLASH Bank1 ******************************************************* */ 
        /* Unlock the Flash Bank1 Program Erase controller */ 
        FLASH_UnlockBank1 ();
    
        /* Define the number of page to be erased */ 
        NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;
    
        /* Clear All pending flags */ 
        FLASH_ClearFlag (FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    
        /* Erase the FLASH pages */ 
        for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
        
    {
        
    
    
        /* Program Flash Bank1 */ 
        Address = BANK1_WRITE_START_ADDR;
    
        
    {
        
        
    
    
    
        /* Check the corectness of written data */ 
        Address = BANK1_WRITE_START_ADDR;
    
        
    {
        
            
        {
            
        
        
    
    
#ifdef STM32F10X_XL
        /* Porgram FLASH Bank2 ******************************************************* */ 
        /* Unlock the Flash Bank2 Program Erase controller */ 
        FLASH_UnlockBank2 ();
    
        /* Define the number of page to be erased */ 
        NbrOfPage = (BANK2_WRITE_END_ADDR - BANK2_WRITE_START_ADDR) / FLASH_PAGE_SIZE;
    
        /* Clear All pending flags */ 
        FLASH_ClearFlag (FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    
        /* Erase the FLASH pages */ 
        for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
        
    {
        
    
    
        /* Program Flash Bank2 */ 
        Address = BANK2_WRITE_START_ADDR;
    
        
    {
        
        
    
    
    
        /* Check the corectness of written data */ 
        Address = BANK2_WRITE_START_ADDR;
    
        
    {
        
            
        {
            
        
        
    
    
#endif  /* STM32F10X_XL */ 
        
        
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
        
        
    {
    



#endif /* 
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 