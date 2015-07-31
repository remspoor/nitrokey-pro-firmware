/**
  ******************************************************************************
  * @file    stm32_eval_sdio_sd.c
  * @author  MCD Application Team
  * @version V4.2.0
  * @date    04/16/2010
  * @brief   This file provides a set of functions needed to manage the SDIO SD 
  *          Card memory mounted on STM32xx-EVAL board (refer to stm32_eval.h
  *          to know about the boards supporting this memory). 
  *          It implements a high level communication layer for read and write 
  *          from/to this memory. The needed STM32 hardware resources (SDIO and 
  *          GPIO) are defined in stm32xx_eval.h file, and the initialization is 
  *          performed in SD_LowLevel_Init() function declared in stm32xx_eval.c 
  *          file.
  *          You can easily tailor this driver to any other development board, 
  *          by just adapting the defines for hardware resources and 
  *          SD_LowLevel_Init() function.
  *            
  *          +-----------------------------------------------------------+
  *          |                     Pin assignment                        |
  *          +-----------------------------+---------------+-------------+
  *          |  STM32 SDIO Pins            |     SD        |    Pin      |
  *          +-----------------------------+---------------+-------------+
  *          |      SDIO D2                |   D2          |    1        |
  *          |      SDIO D3                |   D3          |    2        |
  *          |      SDIO CMD               |   CMD         |    3        |
  *          |                             |   VCC         |    4 (3.3 V)|
  *          |      SDIO CLK               |   CLK         |    5        |
  *          |                             |   GND         |    6 (0 V)  |
  *          |      SDIO D0                |   D0          |    7        |
  *          |      SDIO D1                |   D1          |    8        |  
  *          +-----------------------------+---------------+-------------+   
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
#include "stm32_eval_sdio_sd.h"
    
/** @addtogroup Utilities
  * @{
  */ 
    
/** @addtogroup STM32_EVAL
  * @{
  */ 
    
/** @addtogroup Common
  * @{
  */ 
    
/** @addtogroup STM32_EVAL_SDIO_SD
  * @brief      This file provides all the SD Card driver firmware functions.
  * @{
  */ 
    
/** @defgroup STM32_EVAL_SDIO_SD_Private_Types
  * @{
  */ 
/**
  * @}
  */ 
    
/** @defgroup STM32_EVAL_SDIO_SD_Private_Defines
  * @{
  */ 
/** 
  * @brief  SDIO Static flags, TimeOut, FIFO Address  
  */ 
#define NULL 0
#define SDIO_STATIC_FLAGS               ((uint32_t)0x000005FF)
#define SDIO_CMD0TIMEOUT                ((uint32_t)0x00010000)
    
/** 
  * @brief  Mask for errors Card Status R1 (OCR Register) 
  */ 
#define SD_OCR_ADDR_OUT_OF_RANGE        ((uint32_t)0x80000000)
#define SD_OCR_ADDR_MISALIGNED          ((uint32_t)0x40000000)
#define SD_OCR_BLOCK_LEN_ERR            ((uint32_t)0x20000000)
#define SD_OCR_ERASE_SEQ_ERR            ((uint32_t)0x10000000)
#define SD_OCR_BAD_ERASE_PARAM          ((uint32_t)0x08000000)
#define SD_OCR_WRITE_PROT_VIOLATION     ((uint32_t)0x04000000)
#define SD_OCR_LOCK_UNLOCK_FAILED       ((uint32_t)0x01000000)
#define SD_OCR_COM_CRC_FAILED           ((uint32_t)0x00800000)
#define SD_OCR_ILLEGAL_CMD              ((uint32_t)0x00400000)
#define SD_OCR_CARD_ECC_FAILED          ((uint32_t)0x00200000)
#define SD_OCR_CC_ERROR                 ((uint32_t)0x00100000)
#define SD_OCR_GENERAL_UNKNOWN_ERROR    ((uint32_t)0x00080000)
#define SD_OCR_STREAM_READ_UNDERRUN     ((uint32_t)0x00040000)
#define SD_OCR_STREAM_WRITE_OVERRUN     ((uint32_t)0x00020000)
#define SD_OCR_CID_CSD_OVERWRIETE       ((uint32_t)0x00010000)
#define SD_OCR_WP_ERASE_SKIP            ((uint32_t)0x00008000)
#define SD_OCR_CARD_ECC_DISABLED        ((uint32_t)0x00004000)
#define SD_OCR_ERASE_RESET              ((uint32_t)0x00002000)
#define SD_OCR_AKE_SEQ_ERROR            ((uint32_t)0x00000008)
#define SD_OCR_ERRORBITS                ((uint32_t)0xFDFFE008)
    
/** 
  * @brief  Masks for R6 Response 
  */ 
#define SD_R6_GENERAL_UNKNOWN_ERROR     ((uint32_t)0x00002000)
#define SD_R6_ILLEGAL_CMD               ((uint32_t)0x00004000)
#define SD_R6_COM_CRC_FAILED            ((uint32_t)0x00008000)
    
#define SD_VOLTAGE_WINDOW_SD            ((uint32_t)0x80100000)
#define SD_HIGH_CAPACITY                ((uint32_t)0x40000000)
#define SD_STD_CAPACITY                 ((uint32_t)0x00000000)
#define SD_CHECK_PATTERN                ((uint32_t)0x000001AA)
    
#define SD_MAX_VOLT_TRIAL               ((uint32_t)0x0000FFFF)
#define SD_ALLZERO                      ((uint32_t)0x00000000)
    
#define SD_WIDE_BUS_SUPPORT             ((uint32_t)0x00040000)
#define SD_SINGLE_BUS_SUPPORT           ((uint32_t)0x00010000)
#define SD_CARD_LOCKED                  ((uint32_t)0x02000000)
    
#define SD_DATATIMEOUT                  ((uint32_t)0x000FFFFF)
#define SD_0TO7BITS                     ((uint32_t)0x000000FF)
#define SD_8TO15BITS                    ((uint32_t)0x0000FF00)
#define SD_16TO23BITS                   ((uint32_t)0x00FF0000)
#define SD_24TO31BITS                   ((uint32_t)0xFF000000)
#define SD_MAX_DATA_LENGTH              ((uint32_t)0x01FFFFFF)
    
#define SD_HALFFIFO                     ((uint32_t)0x00000008)
#define SD_HALFFIFOBYTES                ((uint32_t)0x00000020)
    
/** 
  * @brief  Command Class Supported 
  */ 
#define SD_CCCC_LOCK_UNLOCK             ((uint32_t)0x00000080)
#define SD_CCCC_WRITE_PROT              ((uint32_t)0x00000040)
#define SD_CCCC_ERASE                   ((uint32_t)0x00000020)
    
/** 
  * @brief  Following commands are SD Card Specific commands.
  *         SDIO_APP_CMD should be sent before sending these commands. 
  */ 
#define SDIO_SEND_IF_COND               ((uint32_t)0x00000008)
    
/**
  * @}
  */ 
    
/** @defgroup STM32_EVAL_SDIO_SD_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 
    
/** @defgroup STM32_EVAL_SDIO_SD_Private_Variables
  * @{
  */ 
static uint32_t CardType = SDIO_STD_CAPACITY_SD_CARD_V1_1;















/**
  * @}
  */ 
    
/** @defgroup STM32_EVAL_SDIO_SD_Private_Function_Prototypes
  * @{
  */ 
static SD_Error CmdError (void);




















/**
  * @}
  */ 
    
/** @defgroup STM32_EVAL_SDIO_SD_Private_Functions
  * @{
  */ 
    
/**
  * @brief  DeInitializes the SDIO interface.
  * @param  None
  * @retval None
  */ 
void SD_DeInit (void) 
{
    


/**
  * @brief  Initializes the SD Card and put it into StandBy State (Ready for data 
  *         transfer).
  * @param  None
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_Init (void) 
{
    
    
    
        /* SDIO Peripheral Low Level Init */ 
        SD_LowLevel_Init ();
    
    
    
        
    {
        
            /* !< CMD Response TimeOut (wait for CMDSENT flag) */ 
            return (errorstatus);
    
    
    
        
    {
        
            /* !< CMD Response TimeOut (wait for CMDSENT flag) */ 
            return (errorstatus);
    
    
        /* !< Configure the SDIO peripheral */ 
        /* !< SDIOCLK = HCLK, SDIO_CK = HCLK/(2 + SDIO_TRANSFER_CLK_DIV) */ 
        SDIO_InitStructure.SDIO_ClockDiv = SDIO_TRANSFER_CLK_DIV;
    
    
    
    
    
    
    
        
    {
        
    /*----------------- Read CSD/CID MSD registers ------------------*/ 
            errorstatus = SD_GetCardInfo (&sdcardinfo);
    
    
        
    {
        
    /*----------------- Select Card --------------------------------*/ 
            errorstatus = SD_SelectDeselect ((uint32_t) (sdcardinfo.RCA << 16));
    
    
        
    {
        
    
    
        /* Set Device Transfer Mode to DMA */ 
        if (errorstatus == SD_OK)
        
    {
        
    
    



/**
  * @brief  Gets the cuurent sd card data transfer status.
  * @param  None
  * @retval SDTransferState: Data Transfer state.
  *   This value can be: 
  *        - SD_TRANSFER_OK: No data transfer is acting
  *        - SD_TRANSFER_BUSY: Data transfer is acting
  */ 
    SDTransferState SD_GetStatus (void) 
{
    
    
    
        
    {
        
    
    
    else if (cardstate == SD_CARD_ERROR)
        
    {
        
    
    
    else
        
    {
        
    



/**
  * @brief  Returns the current card's state.
  * @param  None
  * @retval SDCardState: SD Card Error or SD Card Current State.
  */ 
    SDCardState SD_GetState (void) 
{
    
    
        
    {
        
            
        {
            
        
        
        else
            
        {
            
        
    
    
    else
        
    {
        
    



/**
 * @brief  Detect if SD card is correctly plugged in the memory slot.
 * @param  None
 * @retval Return if SD is detected or not
 */ 
    uint8_t SD_Detect (void) 
{
    
    
        /* !< Check GPIO to detect SD */ 
        if (GPIO_ReadInputDataBit (SD_DETECT_GPIO_PORT, SD_DETECT_PIN) != Bit_RESET)
        
    {
        
    
    



/**
  * @brief  Enquires cards about their operating voltage and configures 
  *   clock controls.
  * @param  None
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_PowerON (void) 
{
    
    
    
    
    
        /* !< Power ON Sequence ----------------------------------------------------- */ 
        /* !< Configure the SDIO peripheral */ 
        /* !< SDIOCLK = HCLK, SDIO_CK = HCLK/(2 + SDIO_INIT_CLK_DIV) */ 
        /* !< SDIO_CK for initialization should not exceed 400 KHz */ 
        SDIO_InitStructure.SDIO_ClockDiv = SDIO_INIT_CLK_DIV;
    
    
    
    
    
    
    
        /* !< Set Power State to ON */ 
        SDIO_SetPowerState (SDIO_PowerState_ON);
    
        /* !< Enable SDIO Clock */ 
        SDIO_ClockCmd (ENABLE);
    
        /* !< CMD0: GO_IDLE_STATE --------------------------------------------------- */ 
        /* !< No CMD response required */ 
        SDIO_CmdInitStructure.SDIO_Argument = 0x0;
    
    
    
    
    
    
    
        
    {
        
            /* !< CMD Response TimeOut (wait for CMDSENT flag) */ 
            return (errorstatus);
    
    
        /* !< CMD8: SEND_IF_COND ---------------------------------------------------- */ 
        /* !< Send CMD8 to verify SD card interface operating condition */ 
        /* !< Argument: - [31:12]: Reserved (shall be set to '0')
           (recommended 0xAA) */ 
        /* !< CMD Response: R7 */ 
        SDIO_CmdInitStructure.SDIO_Argument = SD_CHECK_PATTERN;
    
    
    
    
    
    
    
        
    {
        
        
    
    
    else
        
    {
        
            /* !< CMD55 */ 
            SDIO_CmdInitStructure.SDIO_Argument = 0x00;
        
        
        
        
        
        
    
    
        /* !< CMD55 */ 
        SDIO_CmdInitStructure.SDIO_Argument = 0x00;
    
    
    
    
    
    
    
        /* !< If errorstatus is Command TimeOut, it is a MMC card */ 
        /* !< If errorstatus is SD_OK it is a SD card: SD card 2.0 (voltage range mismatch)
        if (errorstatus == SD_OK)
        
    {
        
            /* !< SD CARD */ 
            /* !< Send ACMD41 SD_APP_OP_COND with Argument 0x80100000 */ 
            while ((!validvoltage) && (count < SD_MAX_VOLT_TRIAL))
            
        {
            
                /* !< SEND CMD55 APP_CMD with RCA as 0 */ 
                SDIO_CmdInitStructure.SDIO_Argument = 0x00;
            
            
            
            
            
            
            
                
            {
                
            
            
            
            
            
            
            
            
            
                
            {
                
            
            
            
            
        
        
            
        {
            
            
        
        
            
        {
            
        
    
    



/**
  * @brief  Turns the SDIO output signals off.
  * @param  None
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_PowerOFF (void) 
{
    
    
        /* !< Set Power State to OFF */ 
        SDIO_SetPowerState (SDIO_PowerState_OFF);
    



/**
  * @brief  Intialises all cards or single card as the case may be Card(s) come 
  *         into standby state.
  * @param  None
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_InitializeCards (void) 
{
    
    
    
        
    {
        
        
    
    
        
    {
        
            /* !< Send CMD2 ALL_SEND_CID */ 
            SDIO_CmdInitStructure.SDIO_Argument = 0x0;
        
        
        
        
        
        
        
            
        {
            
        
        
        
        
        
    
    
         || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType)
         || (SDIO_SECURE_DIGITAL_IO_COMBO_CARD == CardType) 
        
    {
        
            /* !< Send CMD3 SET_REL_ADDR with argument 0 */ 
            /* !< SD Card publishes its RCA. */ 
            SDIO_CmdInitStructure.SDIO_Argument = 0x00;
        
        
        
        
        
        
        
            
        {
            
        
    
    
        
    {
        
        
            /* !< Send CMD9 SEND_CSD with argument as card's RCA */ 
            SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) (rca << 16);
        
        
        
        
        
        
        
            
        {
            
        
        
        
        
        
    
    
    



/**
  * @brief  Returns information about specific card.
  * @param  cardinfo: pointer to a SD_CardInfo structure that contains all SD card 
  *         information.
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_GetCardInfo (SD_CardInfo * cardinfo) 
{
    
    
    
    
    
        /* !< Byte 0 */ 
        tmp = (uint8_t) ((CSD_Tab[0] & 0xFF000000) >> 24);
    
    
    
    
        /* !< Byte 1 */ 
        tmp = (uint8_t) ((CSD_Tab[0] & 0x00FF0000) >> 16);
    
    
        /* !< Byte 2 */ 
        tmp = (uint8_t) ((CSD_Tab[0] & 0x0000FF00) >> 8);
    
    
        /* !< Byte 3 */ 
        tmp = (uint8_t) (CSD_Tab[0] & 0x000000FF);
    
    
        /* !< Byte 4 */ 
        tmp = (uint8_t) ((CSD_Tab[1] & 0xFF000000) >> 24);
    
    
        /* !< Byte 5 */ 
        tmp = (uint8_t) ((CSD_Tab[1] & 0x00FF0000) >> 16);
    
    
    
        /* !< Byte 6 */ 
        tmp = (uint8_t) ((CSD_Tab[1] & 0x0000FF00) >> 8);
    
    
    
    
    
    
        
    {
        
        
            /* !< Byte 7 */ 
            tmp = (uint8_t) (CSD_Tab[1] & 0x000000FF);
        
        
            /* !< Byte 8 */ 
            tmp = (uint8_t) ((CSD_Tab[2] & 0xFF000000) >> 24);
        
        
        
        
            /* !< Byte 9 */ 
            tmp = (uint8_t) ((CSD_Tab[2] & 0x00FF0000) >> 16);
        
        
        
        
            /* !< Byte 10 */ 
            tmp = (uint8_t) ((CSD_Tab[2] & 0x0000FF00) >> 8);
        
        
        
        
        
    
    
    else if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)
        
    {
        
            /* !< Byte 7 */ 
            tmp = (uint8_t) (CSD_Tab[1] & 0x000000FF);
        
        
            /* !< Byte 8 */ 
            tmp = (uint8_t) ((CSD_Tab[2] & 0xFF000000) >> 24);
        
        
            /* !< Byte 9 */ 
            tmp = (uint8_t) ((CSD_Tab[2] & 0x00FF0000) >> 16);
        
        
            /* !< Byte 10 */ 
            tmp = (uint8_t) ((CSD_Tab[2] & 0x0000FF00) >> 8);
        
        
    
    
    
    
        /* !< Byte 11 */ 
        tmp = (uint8_t) (CSD_Tab[2] & 0x000000FF);
    
    
    
        /* !< Byte 12 */ 
        tmp = (uint8_t) ((CSD_Tab[3] & 0xFF000000) >> 24);
    
    
    
    
    
        /* !< Byte 13 */ 
        tmp = (uint8_t) ((CSD_Tab[3] & 0x00FF0000) >> 16);
    
    
    
    
    
        /* !< Byte 14 */ 
        tmp = (uint8_t) ((CSD_Tab[3] & 0x0000FF00) >> 8);
    
    
    
    
    
    
    
        /* !< Byte 15 */ 
        tmp = (uint8_t) (CSD_Tab[3] & 0x000000FF);
    
    
    
        /* !< Byte 0 */ 
        tmp = (uint8_t) ((CID_Tab[0] & 0xFF000000) >> 24);
    
    
        /* !< Byte 1 */ 
        tmp = (uint8_t) ((CID_Tab[0] & 0x00FF0000) >> 16);
    
    
        /* !< Byte 2 */ 
        tmp = (uint8_t) ((CID_Tab[0] & 0x000000FF00) >> 8);
    
    
        /* !< Byte 3 */ 
        tmp = (uint8_t) (CID_Tab[0] & 0x000000FF);
    
    
        /* !< Byte 4 */ 
        tmp = (uint8_t) ((CID_Tab[1] & 0xFF000000) >> 24);
    
    
        /* !< Byte 5 */ 
        tmp = (uint8_t) ((CID_Tab[1] & 0x00FF0000) >> 16);
    
    
        /* !< Byte 6 */ 
        tmp = (uint8_t) ((CID_Tab[1] & 0x0000FF00) >> 8);
    
    
        /* !< Byte 7 */ 
        tmp = (uint8_t) (CID_Tab[1] & 0x000000FF);
    
    
        /* !< Byte 8 */ 
        tmp = (uint8_t) ((CID_Tab[2] & 0xFF000000) >> 24);
    
    
        /* !< Byte 9 */ 
        tmp = (uint8_t) ((CID_Tab[2] & 0x00FF0000) >> 16);
    
    
        /* !< Byte 10 */ 
        tmp = (uint8_t) ((CID_Tab[2] & 0x0000FF00) >> 8);
    
    
        /* !< Byte 11 */ 
        tmp = (uint8_t) (CID_Tab[2] & 0x000000FF);
    
    
        /* !< Byte 12 */ 
        tmp = (uint8_t) ((CID_Tab[3] & 0xFF000000) >> 24);
    
    
        /* !< Byte 13 */ 
        tmp = (uint8_t) ((CID_Tab[3] & 0x00FF0000) >> 16);
    
    
    
        /* !< Byte 14 */ 
        tmp = (uint8_t) ((CID_Tab[3] & 0x0000FF00) >> 8);
    
    
        /* !< Byte 15 */ 
        tmp = (uint8_t) (CID_Tab[3] & 0x000000FF);
    
    
    



/**
  * @brief  Enables wide bus opeartion for the requeseted card if supported by 
  *         card.
  * @param  WideMode: Specifies the SD card wide bus mode. 
  *   This parameter can be one of the following values:
  *     @arg SDIO_BusWide_8b: 8-bit data transfer (Only for MMC)
  *     @arg SDIO_BusWide_4b: 4-bit data transfer
  *     @arg SDIO_BusWide_1b: 1-bit data transfer
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_EnableWideBusOperation (uint32_t WideMode) 
{
    
    
        /* !< MMC Card doesn't support this feature */ 
        if (SDIO_MULTIMEDIA_CARD == CardType)
        
    {
        
        
    
    
    else if ((SDIO_STD_CAPACITY_SD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_SD_CARD == CardType))
        
    {
        
            
        {
            
            
        
        
        else if (SDIO_BusWide_4b == WideMode)
            
        {
            
            
                
            {
                
                    /* !< Configure the SDIO peripheral */ 
                    SDIO_InitStructure.SDIO_ClockDiv = SDIO_TRANSFER_CLK_DIV;
                
                
                
                
                
#ifdef USE_STM3210E_EVAL
                    SDIO_InitStructure.SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
                
#else /* 
                    SDIO_InitStructure.SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Enable;
                
#endif /* 
                    SDIO_Init (&SDIO_InitStructure);
            
        
        
        else
            
        {
            
            
                
            {
                
                    /* !< Configure the SDIO peripheral */ 
                    SDIO_InitStructure.SDIO_ClockDiv = SDIO_TRANSFER_CLK_DIV;
                
                
                
                
                
#ifdef USE_STM3210E_EVAL
                    SDIO_InitStructure.SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
                
#else /* 
                    SDIO_InitStructure.SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Enable;
                
#endif /* 
                    SDIO_Init (&SDIO_InitStructure);
            
        
    
    



/**
  * @brief  Sets device mode whether to operate in Polling, Interrupt or DMA mode.
  * @param  Mode: Specifies the Data Transfer mode.
  *   This parameter can be one of the following values:
  *     @arg SD_DMA_MODE: Data transfer using DMA.
  *     @arg SD_INTERRUPT_MODE: Data transfer using interrupts.
  *     @arg SD_POLLING_MODE: Data transfer using flags.
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_SetDeviceMode (uint32_t Mode) 
{
    
    
        
    {
        
    
    
    else
        
    {
        
    
    



/**
  * @brief  Selects od Deselects the corresponding card.
  * @param  addr: Address of the Card to be selected.
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_SelectDeselect (uint32_t addr) 
{
    
    
        /* !< Send CMD7 SDIO_SEL_DESEL_CARD */ 
        SDIO_CmdInitStructure.SDIO_Argument = addr;
    
    
    
    
    
    
    



/**
  * @brief  Allows to read one block from a specified address in a card.
  * @param  readbuff: pointer to the buffer that will contain the received data
  * @param  ReadAddr: Address from where data are to be read.  
  * @param  BlockSize: the SD card Data block size.
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_ReadBlock (uint8_t * readbuff, uint32_t ReadAddr, uint16_t BlockSize) 
{
    
    
    
    
        
    {
        
        
    
    
    
    
    
        /* !< Clear all DPSM configuration */ 
        SDIO_DataInitStructure.SDIO_DataTimeOut = SD_DATATIMEOUT;
    
    
    
    
    
    
    
    
        
    {
        
        
    
    
        
    {
        
        
    
    
        
    {
        
        
            /* !< Set Block Size for Card */ 
            SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) BlockSize;
        
        
        
        
        
        
        
            
        {
            
        
    
    
    else
        
    {
        
        
    
    
    
    
    
    
    
    
    
    
    
    
        /* !< Send CMD17 READ_SINGLE_BLOCK */ 
        SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) ReadAddr;
    
    
    
    
    
    
    
        
    {
        
    
    
        /* !< In case of single block transfer, no need of stop transfer at all. */ 
        if (DeviceMode == SD_POLLING_MODE)
        
    {
        
            /* !< Polling mode */ 
            while (!(SDIO->STA & (SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_DBCKEND | SDIO_FLAG_STBITERR)))
            
        {
            
                
            {
                
                    
                {
                    
                
                
            
        
        
            
        {
            
            
            
        
        
        else if (SDIO_GetFlagStatus (SDIO_FLAG_DCRCFAIL) != RESET)
            
        {
            
            
            
        
        
        else if (SDIO_GetFlagStatus (SDIO_FLAG_RXOVERR) != RESET)
            
        {
            
            
            
        
        
        else if (SDIO_GetFlagStatus (SDIO_FLAG_STBITERR) != RESET)
            
        {
            
            
            
        
        
            
        {
            
            
        
        
            /* !< Clear all the static flags */ 
            SDIO_ClearFlag (SDIO_STATIC_FLAGS);
    
    
    else if (DeviceMode == SD_INTERRUPT_MODE)
        
    {
        
        
            
        {
        }
        
            
        {
            
        
    
    
    else if (DeviceMode == SD_DMA_MODE)
        
    {
        
        
        
        
    
    



/**
  * @brief  Allows to read blocks from a specified address  in a card.
  * @param  readbuff: pointer to the buffer that will contain the received data.
  * @param  ReadAddr: Address from where data are to be read.
  * @param  BlockSize: the SD card Data block size.
  * @param  NumberOfBlocks: number of blocks to be read.
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_ReadMultiBlocks (uint8_t * readbuff, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks) 
{
    
    
    
    
        
    {
        
        
    
    
    
    
    
        /* !< Clear all DPSM configuration */ 
        SDIO_DataInitStructure.SDIO_DataTimeOut = SD_DATATIMEOUT;
    
    
    
    
    
    
    
    
        
    {
        
        
    
    
        
    {
        
        
    
    
        
    {
        
        
            /* !< Set Block Size for Card */ 
            SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) BlockSize;
        
        
        
        
        
        
        
            
        {
            
        
    
    
    else
        
    {
        
        
    
    
        
    {
        
            /* !< Common to all modes */ 
            if (NumberOfBlocks * BlockSize > SD_MAX_DATA_LENGTH)
            
        {
            
            
        
        
        
        
        
        
        
        
        
        
        
        
            /* !< Send CMD18 READ_MULT_BLOCK with argument data address */ 
            SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) ReadAddr;
        
        
        
        
        
        
        
            
        {
            
        
        
            
        {
            
                /* !< Polling mode */ 
                while (!(SDIO->STA & (SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DATAEND | SDIO_FLAG_DTIMEOUT | SDIO_FLAG_STBITERR)))
                
            {
                
                    
                {
                    
                        
                    {
                        
                    
                    
                
            
            
                
            {
                
                
                
            
            
            else if (SDIO_GetFlagStatus (SDIO_FLAG_DCRCFAIL) != RESET)
                
            {
                
                
                
            
            
            else if (SDIO_GetFlagStatus (SDIO_FLAG_RXOVERR) != RESET)
                
            {
                
                
                
            
            
            else if (SDIO_GetFlagStatus (SDIO_FLAG_STBITERR) != RESET)
                
            {
                
                
                
            
            
                
            {
                
                
            
            
                
            {
                
                    /* !< In Case Of SD-CARD Send Command STOP_TRANSMISSION */ 
                    if ((SDIO_STD_CAPACITY_SD_CARD_V1_1 == CardType)
                        || (SDIO_HIGH_CAPACITY_SD_CARD == CardType) || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType))
                    
                {
                    
                        /* !< Send CMD12 STOP_TRANSMISSION */ 
                        SDIO_CmdInitStructure.SDIO_Argument = 0x0;
                    
                    
                    
                    
                    
                    
                    
                        
                    {
                        
                    
                
            
            
                /* !< Clear all the static flags */ 
                SDIO_ClearFlag (SDIO_STATIC_FLAGS);
        
        
        else if (DeviceMode == SD_INTERRUPT_MODE)
            
        {
            
            
                
            {
            }
            
                
            {
                
            
        
        
        else if (DeviceMode == SD_DMA_MODE)
            
        {
            
            
            
            
            
                
            {
            }
            
                
            {
                
            
        
    
    



/**
  * @brief  Allows to write one block starting from a specified address in a card.
  * @param  writebuff: pointer to the buffer that contain the data to be transferred.
  * @param  WriteAddr: Address from where data are to be read.   
  * @param  BlockSize: the SD card Data block size.
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_WriteBlock (uint8_t * writebuff, uint32_t WriteAddr, uint16_t BlockSize) 
{
    
    
    
    
    
    
        
    {
        
        
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    {
        
        
    
    
        
    {
        
        
    
    
        /* !< Set the block size, both on controller and card */ 
        if ((BlockSize > 0) && (BlockSize <= 2048) && ((BlockSize & (BlockSize - 1)) == 0))
        
    {
        
        
        
        
        
        
        
        
        
            
        {
            
        
    
    
    else
        
    {
        
        
    
    
        /* !< Wait till card is ready for data Added */ 
        SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) (RCA << 16);
    
    
    
    
    
    
    
        
    {
        
    
    
    
    
        
    {
        
        
        
        
        
        
        
        
        
            
        {
            
        
        
    
    
        
    {
        
    
    
        /* !< Send CMD24 WRITE_SINGLE_BLOCK */ 
        SDIO_CmdInitStructure.SDIO_Argument = WriteAddr;
    
    
    
    
    
    
    
        
    {
        
    
    
    
    
    
    
    
    
    
    
    
    
        /* !< In case of single data block transfer no need of stop command at all */ 
        if (DeviceMode == SD_POLLING_MODE)
        
    {
        
            
        {
            
                
            {
                
                    
                {
                    
                        ((TotalNumberOfBytes - bytestransferred) % 4 ==
                         0) ? ((TotalNumberOfBytes - bytestransferred) / 4) : ((TotalNumberOfBytes - bytestransferred) / 4 + 1);
                    
                        
                    {
                        
                    
                
                
                else
                    
                {
                    
                        
                    {
                        
                    
                    
                    
                
            
        
        
            
        {
            
            
            
        
        
        else if (SDIO_GetFlagStatus (SDIO_FLAG_DCRCFAIL) != RESET)
            
        {
            
            
            
        
        
        else if (SDIO_GetFlagStatus (SDIO_FLAG_TXUNDERR) != RESET)
            
        {
            
            
            
        
        
        else if (SDIO_GetFlagStatus (SDIO_FLAG_STBITERR) != RESET)
            
        {
            
            
            
        
    
    
    else if (DeviceMode == SD_INTERRUPT_MODE)
        
    {
        
        
            
        {
        }
        
            
        {
            
        
    
    
    else if (DeviceMode == SD_DMA_MODE)
        
    {
        
        
        
        
        
            
        {
        }
        
            
        {
            
        
    
    
        /* !< Clear all the static flags */ 
        SDIO_ClearFlag (SDIO_STATIC_FLAGS);
    
        /* !< Wait till the card is in programming state */ 
        errorstatus = IsCardProgramming (&cardstate);
    
        
    {
        
    
    



/**
  * @brief  Allows to write blocks starting from a specified address in a card.
  * @param  WriteAddr: Address from where data are to be read.
  * @param  writebuff: pointer to the buffer that contain the data to be transferred.
  * @param  BlockSize: the SD card Data block size.
  * @param  NumberOfBlocks: number of blocks to be written.
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_WriteMultiBlocks (uint8_t * writebuff, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks) 
{
    
    
    
    
    
    
        
    {
        
        
    
    
    
    
    
    
    
    
    
    
    
    
    
        
    {
        
        
    
    
        
    {
        
        
    
    
        /* !< Set the block size, both on controller and card */ 
        if ((BlockSize > 0) && (BlockSize <= 2048) && ((BlockSize & (BlockSize - 1)) == 0))
        
    {
        
        
        
        
        
        
        
        
        
            
        {
            
        
    
    
    else
        
    {
        
        
    
    
        /* !< Wait till card is ready for data Added */ 
        SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) (RCA << 16);
    
    
    
    
    
    
    
        
    {
        
    
    
        
    {
        
            /* !< Common to all modes */ 
            if (NumberOfBlocks * BlockSize > SD_MAX_DATA_LENGTH)
            
        {
            
            
        
        
              || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_SD_CARD == CardType))
            
        {
            
                /* !< To improve performance */ 
                SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) (RCA << 16);
            
            
            
            
            
            
            
                
            {
                
            
            
                /* !< To improve performance */ 
                SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) NumberOfBlocks;
            
            
            
            
            
            
            
                
            {
                
            
        
        
            /* !< Send CMD25 WRITE_MULT_BLOCK with argument data address */ 
            SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) WriteAddr;
        
        
        
        
        
        
        
            
        {
            
        
        
        
        
        
        
        
        
        
        
        
        
            
        {
            
                
            {
                
                    
                {
                    
                        
                    {
                        
                            
                        {
                            
                        
                        
                        
                    
                    
                    else
                        
                    {
                        
                            ((TotalNumberOfBytes - bytestransferred) % 4 ==
                             0) ? ((TotalNumberOfBytes - bytestransferred) / 4) : 
                        
                            
                        {
                            
                        
                    
                
            
            
                
            {
                
                
                
            
            
            else if (SDIO_GetFlagStatus (SDIO_FLAG_DCRCFAIL) != RESET)
                
            {
                
                
                
            
            
            else if (SDIO_GetFlagStatus (SDIO_FLAG_TXUNDERR) != RESET)
                
            {
                
                
                
            
            
            else if (SDIO_GetFlagStatus (SDIO_FLAG_STBITERR) != RESET)
                
            {
                
                
                
            
            
                
            {
                
                     || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_SD_CARD == CardType))
                    
                {
                    
                        /* !< Send CMD12 STOP_TRANSMISSION */ 
                        SDIO_CmdInitStructure.SDIO_Argument = 0x0;
                    
                    
                    
                    
                    
                    
                    
                        
                    {
                        
                    
                
            
        
        
        else if (DeviceMode == SD_INTERRUPT_MODE)
            
        {
            
            
                
            {
            }
            
                
            {
                
            
        
        
        else if (DeviceMode == SD_DMA_MODE)
            
        {
            
            
            
            
            
                
            {
            }
            
                
            {
                
            
        
    
    
        /* !< Clear all the static flags */ 
        SDIO_ClearFlag (SDIO_STATIC_FLAGS);
    
        /* !< Wait till the card is in programming state */ 
        errorstatus = IsCardProgramming (&cardstate);
    
        
    {
        
    
    



/**
  * @brief  Gets the cuurent data transfer state.
  * @param  None
  * @retval SDTransferState: Data Transfer state.
  *   This value can be: 
  *        - SD_TRANSFER_OK: No data transfer is acting
  *        - SD_TRANSFER_BUSY: Data transfer is acting
  */ 
    SDTransferState SD_GetTransferState (void) 
{
    
        
    {
        
    
    
    else
        
    {
        
    



/**
  * @brief  Aborts an ongoing data transfer.
  * @param  None
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_StopTransfer (void) 
{
    
    
        /* !< Send CMD12 STOP_TRANSMISSION */ 
        SDIO_CmdInitStructure.SDIO_Argument = 0x0;
    
    
    
    
    
    
    



/**
  * @brief  Allows to erase memory area specified for the given card.
  * @param  startaddr: the start address.
  * @param  endaddr: the end address.
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_Erase (uint32_t startaddr, uint32_t endaddr) 
{
    
    
    
    
    
        /* !< Check if the card coomnd class supports erase command */ 
        if (((CSD_Tab[1] >> 20) & SD_CCCC_ERASE) == 0)
        
    {
        
        
    
    
    
        
    {
        
        
    
    
        
    {
        
        
    
    
        /* !< According to sd-card spec 1.0 ERASE_GROUP_START (CMD32) and erase_group_end(CMD33) */ 
        if ((SDIO_STD_CAPACITY_SD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_SD_CARD == CardType))
        
    {
        
            /* !< Send CMD32 SD_ERASE_GRP_START with argument as addr */ 
            SDIO_CmdInitStructure.SDIO_Argument = startaddr;
        
        
        
        
        
        
        
            
        {
            
        
        
            /* !< Send CMD33 SD_ERASE_GRP_END with argument as addr */ 
            SDIO_CmdInitStructure.SDIO_Argument = endaddr;
        
        
        
        
        
        
        
            
        {
            
        
    
    
        /* !< Send CMD38 ERASE */ 
        SDIO_CmdInitStructure.SDIO_Argument = 0;
    
    
    
    
    
    
    
        
    {
        
    
    
        
    {
    }
    
        /* !< Wait till the card is in programming state */ 
        errorstatus = IsCardProgramming (&cardstate);
    
        
    {
        
    
    



/**
  * @brief  Returns the current card's status.
  * @param  pcardstatus: pointer to the buffer that will contain the SD card 
  *         status (Card Status register).
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_SendStatus (uint32_t * pcardstatus) 
{
    
    
        
    {
        
        
    
    
    
    
    
    
    
    
    
        
    {
        
    
    
    



/**
  * @brief  Returns the current SD card's status.
  * @param  psdstatus: pointer to the buffer that will contain the SD card status 
  *         (SD Status register).
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_SendSDStatus (uint32_t * psdstatus) 
{
    
    
    
        
    {
        
        
    
    
        /* !< Set block size for card if it is not equal to current block size for card. */ 
        SDIO_CmdInitStructure.SDIO_Argument = 64;
    
    
    
    
    
    
    
        
    {
        
    
    
        /* !< CMD55 */ 
        SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) RCA << 16;
    
    
    
    
    
    
    
        
    {
        
    
    
    
    
    
    
    
    
    
        /* !< Send ACMD13 SD_APP_STAUS with argument as card's RCA. */ 
        SDIO_CmdInitStructure.SDIO_Argument = 0;
    
    
    
    
    
    
    
        
    {
        
    
    
        
    {
        
            
        {
            
                
            {
                
            
            
        
    
    
        
    {
        
        
        
    
    
    else if (SDIO_GetFlagStatus (SDIO_FLAG_DCRCFAIL) != RESET)
        
    {
        
        
        
    
    
    else if (SDIO_GetFlagStatus (SDIO_FLAG_RXOVERR) != RESET)
        
    {
        
        
        
    
    
    else if (SDIO_GetFlagStatus (SDIO_FLAG_STBITERR) != RESET)
        
    {
        
        
        
    
    
        
    {
        
        
    
    
        /* !< Clear all the static status flags */ 
        SDIO_ClearFlag (SDIO_STATIC_FLAGS);
    
    
        
    {
        
            ((psdstatus[count] & SD_0TO7BITS) << 24) |
            ((psdstatus[count] & SD_8TO15BITS) << 8) | 
    
    



/**
  * @brief  Allows to process all the interrupts that are high.
  * @param  None
  * @retval SD_Error: SD Card Error code.
  */ 
    SD_Error SD_ProcessIRQSrc (void) 
{
    
    
        
    {
        
            
        {
            
                
            {
                
            
            
            
        
        
        else if (SDIO_GetITStatus (SDIO_IT_TXFIFOHE) != RESET)
            
        {
            
                
            {
                
                    ((TotalNumberOfBytes - NumberOfBytes) % 4 ==
                     0) ? 
                
                    
                {
                    
                
            
            
            else
                
            {
                
                    
                {
                    
                
                
                
            
        
    
    
        
    {
        
            
        {
            
                
            {
                
                
                
            
        
        
            
        {
            
        
        
        else
            
        {
            
        
        
        
                        | 
        
        
        
    
    
        
    {
        
        
                        | 
        
        
        
    
    
        
    {
        
        
                        | 
        
        
        
    
    
        
    {
        
        
                        | 
        
        
        
    
    
        
    {
        
        
                        | 
        
        
        
    
    
        
    {
        
        
                        | 
        
        
        
    
    



/**
  * @brief  Checks for error conditions for CMD0.
  * @param  None
  * @retval SD_Error: SD Card Error code.
  */ 
static SD_Error CmdError (void) 
{
    
    
    
    
        
    {
        
    
    
        
    {
        
        
    
    
        /* !< Clear all the static flags */ 
        SDIO_ClearFlag (SDIO_STATIC_FLAGS);
    



/**
  * @brief  Checks for error conditions for R7 response.
  * @param  None
  * @retval SD_Error: SD Card Error code.
  */ 
static SD_Error CmdResp7Error (void) 
{
    
    
    
    
    
        
    {
        
        
    
    
        
    {
        
            /* !< Card is not V2.0 complient or card does not support the set voltage range */ 
            errorstatus = SD_CMD_RSP_TIMEOUT;
        
        
    
    
        
    {
        
            /* !< Card is SD V2.0 compliant */ 
            errorstatus = SD_OK;
        
        
    
    



/**
  * @brief  Checks for error conditions for R1 response.
  * @param  cmd: The sent command index.
  * @retval SD_Error: SD Card Error code.
  */ 
static SD_Error CmdResp1Error (uint8_t cmd) 
{
    
    
    
    
    
        
    {
        
    
    
        
    {
        
        
        
    
    
    else if (status & SDIO_FLAG_CCRCFAIL)
        
    {
        
        
        
    
    
        /* !< Check response received is of desired command */ 
        if (SDIO_GetCommandResponse () != cmd)
        
    {
        
        
    
    
        /* !< Clear all the static flags */ 
        SDIO_ClearFlag (SDIO_STATIC_FLAGS);
    
        /* !< We have received response, retrieve it for analysis */ 
        response_r1 = SDIO_GetResponse (SDIO_RESP1);
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    



/**
  * @brief  Checks for error conditions for R3 (OCR) response.
  * @param  None
  * @retval SD_Error: SD Card Error code.
  */ 
static SD_Error CmdResp3Error (void) 
{
    
    
    
    
        
    {
        
    
    
        
    {
        
        
        
    
    
        /* !< Clear all the static flags */ 
        SDIO_ClearFlag (SDIO_STATIC_FLAGS);
    



/**
  * @brief  Checks for error conditions for R2 (CID or CSD) response.
  * @param  None
  * @retval SD_Error: SD Card Error code.
  */ 
static SD_Error CmdResp2Error (void) 
{
    
    
    
    
        
    {
        
    
    
        
    {
        
        
        
    
    
    else if (status & SDIO_FLAG_CCRCFAIL)
        
    {
        
        
        
    
    
        /* !< Clear all the static flags */ 
        SDIO_ClearFlag (SDIO_STATIC_FLAGS);
    



/**
  * @brief  Checks for error conditions for R6 (RCA) response.
  * @param  cmd: The sent command index.
  * @param  prca: pointer to the variable that will contain the SD card relative 
  *         address RCA. 
  * @retval SD_Error: SD Card Error code.
  */ 
static SD_Error CmdResp6Error (uint8_t cmd, uint16_t * prca) 
{
    
    
    
    
    
        
    {
        
    
    
        
    {
        
        
        
    
    
    else if (status & SDIO_FLAG_CCRCFAIL)
        
    {
        
        
        
    
    
        /* !< Check response received is of desired command */ 
        if (SDIO_GetCommandResponse () != cmd)
        
    {
        
        
    
    
        /* !< Clear all the static flags */ 
        SDIO_ClearFlag (SDIO_STATIC_FLAGS);
    
        /* !< We have received response, retrieve it.  */ 
        response_r1 = SDIO_GetResponse (SDIO_RESP1);
    
        
    {
        
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    



/**
  * @brief  Enables or disables the SDIO wide bus mode.
  * @param  NewState: new state of the SDIO wide bus mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval SD_Error: SD Card Error code.
  */ 
static SD_Error SDEnWideBus (FunctionalState NewState) 
{
    
    
    {
    0, 0};
    
        
    {
        
        
    
    
        /* !< Get SCR Register */ 
        errorstatus = FindSCR (RCA, scr);
    
        
    {
        
    
    
        /* !< If wide bus operation to be enabled */ 
        if (NewState == ENABLE)
        
    {
        
            /* !< If requested card supports wide bus operation */ 
            if ((scr[1] & SD_WIDE_BUS_SUPPORT) != SD_ALLZERO)
            
        {
            
                /* !< Send CMD55 APP_CMD with argument as card's RCA. */ 
                SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) RCA << 16;
            
            
            
            
            
            
            
                
            {
                
            
            
                /* !< Send ACMD6 APP_CMD with argument as 2 for wide bus mode */ 
                SDIO_CmdInitStructure.SDIO_Argument = 0x2;
            
            
            
            
            
            
            
                
            {
                
            
            
        
        
        else
            
        {
            
            
        
    
    
    else
        
    {
        
            /* !< If requested card supports 1 bit mode operation */ 
            if ((scr[1] & SD_SINGLE_BUS_SUPPORT) != SD_ALLZERO)
            
        {
            
                /* !< Send CMD55 APP_CMD with argument as card's RCA. */ 
                SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) RCA << 16;
            
            
            
            
            
            
            
                
            {
                
            
            
                /* !< Send ACMD6 APP_CMD with argument as 2 for wide bus mode */ 
                SDIO_CmdInitStructure.SDIO_Argument = 0x00;
            
            
            
            
            
            
            
                
            {
                
            
            
        
        
        else
            
        {
            
            
        
    



/**
  * @brief  Checks if the SD card is in programming state.
  * @param  pstatus: pointer to the variable that will contain the SD card state.
  * @retval SD_Error: SD Card Error code.
  */ 
static SD_Error IsCardProgramming (uint8_t * pstatus) 
{
    
    
    
    
    
    
    
    
    
    
        
    {
        
    
    
        
    {
        
        
        
    
    
    else if (status & SDIO_FLAG_CCRCFAIL)
        
    {
        
        
        
    
    
    
        /* !< Check response received is of desired command */ 
        if (status != SD_CMD_SEND_STATUS)
        
    {
        
        
    
    
        /* !< Clear all the static flags */ 
        SDIO_ClearFlag (SDIO_STATIC_FLAGS);
    
        /* !< We have received response, retrieve it for analysis */ 
        respR1 = SDIO_GetResponse (SDIO_RESP1);
    
        /* !< Find out card status */ 
        *pstatus = (uint8_t) ((respR1 >> 9) & 0x0000000F);
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    
        
    {
        
    
    



/**
  * @brief  Find the SD card SCR register value.
  * @param  rca: selected card address.
  * @param  pscr: pointer to the buffer that will contain the SCR value.
  * @retval SD_Error: SD Card Error code.
  */ 
static SD_Error FindSCR (uint16_t rca, uint32_t * pscr) 
{
    
    
    
    {
    0, 0};
    
        /* !< Set Block Size To 8 Bytes */ 
        /* !< Send CMD55 APP_CMD with argument as card's RCA */ 
        SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) 8;
    
    
    
    
    
    
    
        
    {
        
    
    
        /* !< Send CMD55 APP_CMD with argument as card's RCA */ 
        SDIO_CmdInitStructure.SDIO_Argument = (uint32_t) RCA << 16;
    
    
    
    
    
    
    
        
    {
        
    
    
    
    
    
    
    
    
    
        /* !< Send ACMD51 SD_APP_SEND_SCR with argument as 0 */ 
        SDIO_CmdInitStructure.SDIO_Argument = 0x0;
    
    
    
    
    
    
    
        
    {
        
    
    
        
    {
        
            
        {
            
            
        
    
    
        
    {
        
        
        
    
    
    else if (SDIO_GetFlagStatus (SDIO_FLAG_DCRCFAIL) != RESET)
        
    {
        
        
        
    
    
    else if (SDIO_GetFlagStatus (SDIO_FLAG_RXOVERR) != RESET)
        
    {
        
        
        
    
    
    else if (SDIO_GetFlagStatus (SDIO_FLAG_STBITERR) != RESET)
        
    {
        
        
        
    
    
        /* !< Clear all the static flags */ 
        SDIO_ClearFlag (SDIO_STATIC_FLAGS);
    
        ((tempscr[0] & SD_0TO7BITS) << 24) | ((tempscr[0] & SD_8TO15BITS) <<
                                              8) | ((tempscr[0] & SD_16TO23BITS) >> 8) | ((tempscr[0] & SD_24TO31BITS) >> 24);
    
        ((tempscr[1] & SD_0TO7BITS) << 24) | ((tempscr[1] & SD_8TO15BITS) <<
                                              8) | ((tempscr[1] & SD_16TO23BITS) >> 8) | ((tempscr[1] & SD_24TO31BITS) >> 24);
    



/**
  * @brief  Converts the number of bytes in power of two and returns the power.
  * @param  NumberOfBytes: number of bytes.
  * @retval None
  */ 
static uint8_t convert_from_bytes_to_power_of_two (uint16_t NumberOfBytes) 
{
    
    
        
    {
        
        
    
    



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