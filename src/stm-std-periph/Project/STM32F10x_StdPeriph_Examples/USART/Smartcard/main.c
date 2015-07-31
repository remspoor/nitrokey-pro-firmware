/**
  ******************************************************************************
  * @file USART/Smartcard/main.c 
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
    
    /* Private define ------------------------------------------------------------ */ 
#define T0_PROTOCOL           0x00 /* T0 PROTOCOL */
#define SETUP_LENGHT          20 
#define HIST_LENGHT           20
#define SC_Receive_Timeout    0x4000 /* direction to reader */
    
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */ 
    
/** @addtogroup USART_Smartcard
  * @{
  */ 
    
    /* Private typedef ----------------------------------------------------------- */ 
    /* ATR STRUCTURE - ANSWER TO RESET */ 
typedef struct 
{
    
    
    
    
    
    



{ FAILED = 0, PASSED = !FAILED } TestStatus;


    /* Private macro ------------------------------------------------------------- */ 
    /* Private variables --------------------------------------------------------- */ 
    USART_InitTypeDef USART_InitStructure;







{

        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

    /* Private function prototypes ----------------------------------------------- */ 
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
        
        /* System Clocks Configuration */ 
        RCC_Configuration ();
    
        /* NVIC configuration */ 
        NVIC_Configuration ();
    
        /* Configure the GPIO ports */ 
        GPIO_Configuration ();
    
        /* Configure the EXTI Controller */ 
        EXTI_Configuration ();
    
        /* SC_USART configuration ---------------------------------------------------- */ 
        /* SC_USART configured as follow:
           disabled (RTS and CTS signals)
           Clock Enabled
        
        /* SC_USART Clock set to 4.5MHz (PCLK1 = 36 MHZ / 8) */ 
        USART_SetPrescaler (SC_USART, 0x04);
    
        /* SC_USART Guard Time set to 2 Bit */ 
        USART_SetGuardTime (SC_USART, 0x2);
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* Enable the SC_USART Parity Error Interrupt */ 
        USART_ITConfig (SC_USART, USART_IT_PE, ENABLE);
    
        /* Enable SC_USART */ 
        USART_Cmd (SC_USART, ENABLE);
    
        /* Enable the NACK Transmission */ 
        USART_SmartCardNACKCmd (SC_USART, ENABLE);
    
        /* Enable the Smartcard Interface */ 
        USART_SmartCardCmd (SC_USART, ENABLE);
    
        /* Loop while no Smartcard is detected */ 
        while (CardInserted == 0)
        
    {
    
    
        /* Read Smartcard ATR response */ 
        for (index = 0; index < 40; index++, Counter = 0)
        
    {
        
            
        {
            
        
        
            
        {
            
        
    
    
        /* Decode ATR */ 
        CardProtocol = SC_decode_Answer2reset (DST_Buffer);
    
        /* Test if the inserted card is ISO7816-3 T=0 compatible */ 
        if (CardProtocol == 0)
        
    {
        
            /* Inserted card is ISO7816-3 T=0 compatible */ 
            ATRDecodeStatus = PASSED;
    
    
    else
        
    {
        
            /* Inserted Smartcard is not ISO7816-3 T=0 compatible */ 
            ATRDecodeStatus = FAILED;
    
    
        
    {
    



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */ 
void RCC_Configuration (void) 
{
    
        /* Enable GPIO_3_5V, SC_USART_GPIO_CLK, GPIO_CMDVCC, GPIO_RESET, GPIO_OFF and 
        RCC_APB2PeriphClockCmd (RCC_APB2Periph_3_5V | SC_USART_GPIO_CLK |
                                RCC_APB2Periph_RESET | 
    
        /* Enable SC_USART clocks */ 
        RCC_APB1PeriphClockCmd (SC_USART_CLK, ENABLE);


/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */ 
void GPIO_Configuration (void) 
{
    
    
#ifdef USE_STM3210C_EVAL
        /* Enable the USART3 Pins Software Full Remapping */ 
        GPIO_PinRemapConfig (GPIO_FullRemap_USART3, ENABLE);
    
#endif /* 
        /* Configure SC_USART CK as alternate function push-pull */ 
        GPIO_InitStructure.GPIO_Pin = SC_USART_ClkPin;
    
    
    
    
        /* Configure SC_USART Tx as alternate function open-drain */ 
        GPIO_InitStructure.GPIO_Pin = SC_USART_TxPin;
    
    
    
        /* Configure Smartcard Reset */ 
        GPIO_InitStructure.GPIO_Pin = SC_RESET;
    
    
    
        /* Set RSTIN HIGH */ 
        GPIO_SetBits (GPIO_RESET, SC_RESET);
    
        /* Configure Smartcard 3/5V */ 
        GPIO_InitStructure.GPIO_Pin = SC_3_5V;
    
    
        /* Select 5 V */ 
        GPIO_SetBits (GPIO_3_5V, SC_3_5V);
    
        /* Configure Smartcard CMDVCC */ 
        GPIO_InitStructure.GPIO_Pin = SC_CMDVCC;
    
    
        /* Select Smartcard CMDVCC */ 
        GPIO_SetBits (GPIO_CMDVCC, SC_CMDVCC);
    
        /* Select Smartcard OFF */ 
        GPIO_InitStructure.GPIO_Pin = SC_OFF;
    
    


/**
  * @brief  Configures the External Interrupts controller.
  * @param  None
  * @retval None
  */ 
void EXTI_Configuration (void) 
{
    
    
        /* Smartcard OFF */ 
        GPIO_EXTILineConfig (SC_PortSource, SC_PinSource);
    
    
    
    
    
    
    
        /* Clear SC EXTI Line Pending Bit */ 
        EXTI_ClearITPendingBit (SC_EXTI);


/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */ 
void NVIC_Configuration (void) 
{
    
    
        /* Configure the NVIC Preemption Priority Bits */ 
        NVIC_PriorityGroupConfig (NVIC_PriorityGroup_1);
    
        /* Clear the SC_EXTI IRQ Pending Bit */ 
        NVIC_ClearPendingIRQ (SC_EXTI_IRQ);
    
    
    
    
    
    
    
    
    
    


/**
  * @brief  Decode the Card ATR Response.
  * @param  card: pointer to the buffer containing the Card ATR.
  * @retval Card protocol
  */ 
    uint8_t SC_decode_Answer2reset (__IO uint8_t * card) 
{
    
    
    
    
        
    {
        
    
    
        
    {
        
    
    
    
    
    
    
    
        flag = 1;
    
        
    {
        
    
    
        
    {
        
    
    
    
        
    {
        
            
        {
            
        
        
        else
            
        {
            
        
        
        
        
            
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