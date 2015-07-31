/**
  ******************************************************************************
  * @file    CEC/main.c 
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
#include "stm32_eval.h"
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup CEC_Example
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    typedef enum
{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private define ------------------------------------------------------------ */ 
    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    CEC_InitTypeDef CEC_InitStructure;










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
        
        /* RCC configuration */ 
        RCC_Configuration ();
    
        /* NVIC configuration */ 
        NVIC_Configuration ();
    
        /* GPIO configuration */ 
        GPIO_Configuration ();
    
        /* Configure the CEC peripheral */ 
        CEC_InitStructure.CEC_BitTimingMode = CEC_BitTimingStdMode;
    
    
    
        /* Set Prescaler value for APB1 clock PCLK1 = 24MHz */ 
        CEC_SetPrescaler (0x4AF);
    
        /* Set the CEC initiator address */ 
        CEC_OwnAddressConfig (MY_DEVICE_ADDRESS);
    
        /* Activate CEC interrupts associated to the set of RBTF,RERR, TBTF, TERR flags */ 
        CEC_ITConfig (ENABLE);
    
        /* Enable CEC */ 
        CEC_Cmd (ENABLE);
    
        /* If a frame has been received */ 
        while (ReceivedFrame == 0)
        
    {
    
    
        /* Check the received data with the send ones */ 
        TransferStatus = Buffercmp (TransmitBuffer, ReceiveBuffer, ByteNumber);
    
        /* TransferStatus = PASSED, if the data transmitted from CEC Device1 and 
        /* TransferStatus = FAILED, if the data transmitted from CEC Device1 and 
        
        
    {
        
            /* OK */ 
            /* Turn on LED1 */ 
            STM_EVAL_LEDOn (LED1);
    
    
    else
        
    {
        
            /* KO */ 
            /* Turn on LED2 */ 
            STM_EVAL_LEDOn (LED2);
    
    
        
    {
    



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* Enable CEC clock */ 
        RCC_APB1PeriphClockCmd (RCC_APB1Periph_CEC, ENABLE);
    
        /* Initialize LEDs and Key Button available on STM32F100B-EVAL board ** */ 
        /* Configure LED1, LED2, LED3 and LED4 */ 
        STM_EVAL_LEDInit (LED1);
    
    
    
    
        /* Configure the Key Push button and its associated EXTI Line */ 
        STM_EVAL_PBInit (Button_KEY, Mode_EXTI);


/**
  * @brief  Configures the different NVIC interrupts.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* Configure two bits for preemption priority */ 
        NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2);
    
        /* Enable the CEC global Interrupt (with higher priority) */ 
        NVIC_InitStructure.NVIC_IRQChannel = CEC_IRQn;
    
    
    
    


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
        /* Enable GPIOB clocks */ 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
    
        /* Configure GPIOB Pin 8 (CEC line) as Output open drain */ 
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    
    
    


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
    



#endif /* 
    
/**
  * @}
  */ 
    
/**
  * @}
  */ 
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/ 