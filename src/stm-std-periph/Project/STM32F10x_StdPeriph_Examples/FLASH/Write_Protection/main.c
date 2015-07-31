/**
  ******************************************************************************
  * @file    FLASH/Write_Protection/main.c 
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
    
/** @addtogroup FLASH_Write_Protection
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
    /* Define the STM32F10x FLASH Page Size depending on the used device */ 
#if defined (STM32F10X_HD) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
#define FLASH_PAGE_SIZE    ((uint16_t)0x800)
#else /* 
#define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#endif /* 
    
#define BANK1_WRITE_START_ADDR  ((uint32_t)0x08006000)
#define BANK1_WRITE_END_ADDR    ((uint32_t)0x08008000)
    
    /* Uncomment this line to Enable Write Protection */ 
    // #define WRITE_PROTECTION_ENABLE
    /* Uncomment this line to Disable Write Protection */ 
#define WRITE_PROTECTION_DISABLE
    
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    uint32_t EraseCounter, Address;








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
        
    
    
    
    
        /* Unlock the Flash Program Erase controller */ 
        FLASH_Unlock ();
    
        /* Define the number of page to be erased */ 
        NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;
    
    
        /* Get pages write protection status */ 
        WRPR_Value = FLASH_GetWriteProtectionOptionByte ();
    
    
#ifdef WRITE_PROTECTION_DISABLE
        if (ProtectedPages == 0x00)
        
    {   /* Pages are write protected */
        
            /* Disable the write protection */ 
            FLASHStatus = FLASH_EraseOptionBytes ();
        
            /* Generate System Reset to load the new option byte values */ 
            NVIC_SystemReset ();
    
    
#elif defined WRITE_PROTECTION_ENABLE
        
        
    {   /* Pages not write protected */
        
            /* Enable the pages write protection */ 
#if defined (STM32F10X_HD) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
            FLASHStatus = FLASH_EnableWriteProtection (FLASH_WRProt_Pages12to13 | FLASH_WRProt_Pages14to15);
        
#else /* 
            FLASHStatus = FLASH_EnableWriteProtection (FLASH_WRProt_Pages24to27 | FLASH_WRProt_Pages28to31);
        
#endif /* 
            /* Generate System Reset to load the new option byte values */ 
            NVIC_SystemReset ();
    
    
#endif /* 
        
        /* If Pages are not write protected, perform erase and program operations
        if (ProtectedPages != 0x00)
        
    {
        
            /* Clear All pending flags */ 
            FLASH_ClearFlag (FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
        
            /* erase the FLASH pages */ 
            for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
            
        {
            
        
        
            /* FLASH Half Word program of data 0x1753 at addresses defined by BANK1_WRITE_START_ADDR and BANK1_WRITE_END_ADDR */ 
            Address = BANK1_WRITE_START_ADDR;
        
            
        {
            
            
        
        
            /* Check the corectness of written data */ 
            Address = BANK1_WRITE_START_ADDR;
        
            
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
        
        
    {
    



#endif /* 
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 