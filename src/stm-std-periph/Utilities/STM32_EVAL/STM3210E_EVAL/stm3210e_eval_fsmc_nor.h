/**
  ******************************************************************************
  * @file    stm3210e_eval_fsmc_nor.h
  * @author  MCD Application Team
  * @version V4.2.0
  * @date    04/16/2010
  * @brief   This file contains all the functions prototypes for the 
  *          stm3210e_eval_fsmc_nor firmware driver.
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
    
    /* Define to prevent recursive inclusion ------------------------------------- */ 
#ifndef __STM3210E_EVAL_FSMC_NOR_H
#define __STM3210E_EVAL_FSMC_NOR_H
    
#ifdef __cplusplus
extern "C"
{
    
#endif                          /* 
    
        /* Includes ------------------------------------------------------------------ */ 
#include "stm32f10x.h"
    
/** @addtogroup Utilities
  * @{
  */ 
    
/** @addtogroup STM32_EVAL
  * @{
  */ 
    
/** @addtogroup STM3210E_EVAL
  * @{
  */ 
    
/** @addtogroup STM3210E_EVAL_FSMC_NOR
  * @{
  */ 
    
/** @defgroup STM3210E_EVAL_FSMC_NOR_Exported_Types
  * @{
  */ 
    typedef struct 
    {
        
        
        
        
    
    
        /* NOR Status */ 
    typedef enum 
    { 
    } NOR_Status;
     
/**
  * @}
  */ 
     
/** @defgroup STM3210E_EVAL_FSMC_NOR_Exported_Constants
  * @{
  */ 
/**
  * @}
  */ 
     
/** @defgroup STM3210E_EVAL_FSMC_NOR_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 
     
/** @defgroup STM3210E_EVAL_FSMC_NOR_Exported_Functions
  * @{
  */ 
    void NOR_Init (void);
     
     
     
     
     
     
     
     
     
     
     
    
#ifdef __cplusplus
} 
#endif                          /* 
 
#endif  /* __STM3210E_EVAL_FSMC_NOR_H */
/**
  * @}
  */ 
 
/**
  * @}
  */ 
 
/**
  * @}
  */ 
 
/**
  * @}
  */ 
 
/**
  * @}
  */ 
 
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 