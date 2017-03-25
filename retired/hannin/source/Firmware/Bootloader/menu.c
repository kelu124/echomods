/**
******************************************************************************
* @file    menu.c 
* @author  William Xu
* @version V2.0.0
* @date    05-Oct-2014
* @brief   his file provides the software which contains the main menu routine.
*          The main menu gives the options of:
*             - downloading a new binary file, 
*             - uploading internal flash memory,
*             - executing the binary file already loaded 
******************************************************************************
*
*  The MIT License
*  Copyright (c) 2014 MXCHIP Inc.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy 
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights 
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is furnished
*  to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
*  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "ymodem.h"
#include "platform_config.h"
#include "platformInternal.h"
#include "StringUtils.h"
#include "MicoRtos.h"
#include "MicoPlatform.h"
#include <ctype.h>                    

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CMD_STRING_SIZE       128
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern platform_flash_t platform_flash_peripherals[];

uint8_t tab_1024[1024] =
  {
    0
  };

#if defined MICO_FLASH_FOR_UPDATE && defined MICO_FLASH_FOR_DRIVER
char MEMMAP[] = "\r\n\
+******************** MICO Flash Map **************+\r\n\
+-- Content --+-- Flash ---+-- Start ---+--- End ----+\r\n\
| Bootloader  | %10s | 0x%08x | 0x%08x |\r\n\
| Settings    | %10s | 0x%08x | 0x%08x |\r\n\
| Application | %10s | 0x%08x | 0x%08x |\r\n\
| OTA Storage | %10s | 0x%08x | 0x%08x |\r\n\
| RF Driver   | %10s | 0x%08x | 0x%08x |\r\n\
+-------------+------------+------------+------------+\r\n";
#endif 

#if !defined MICO_FLASH_FOR_UPDATE && defined MICO_FLASH_FOR_DRIVER
char MEMMAP[] = "\r\n\
+******************** MICO Flash Map *****************+\r\n\
+-- Content --+-- Flash ---+--- Start ---+--- End ----+\r\n\
| Bootloader  | %10s | 0x%08x | 0x%08x |\r\n\
| Settings    | %10s | 0x%08x | 0x%08x |\r\n\
| Application | %10s | 0x%08x | 0x%08x |\r\n\
| RF Driver   | %10s | 0x%08x | 0x%08x |\r\n\
+-------------+------------+------------+------------+\r\n";
#endif

#if defined MICO_FLASH_FOR_UPDATE && !defined MICO_FLASH_FOR_DRIVER
char MEMMAP[] = "\r\n\
+******************** MICO Flash Map *****************+\r\n\
+-- Content --+-- Flash ---+--- Start ---+--- End ----+\r\n\
| Bootloader  | %10s | 0x%08x | 0x%08x |\r\n\
| Settings    | %10s | 0x%08x | 0x%08x |\r\n\
| Application | %10s | 0x%08x | 0x%08x |\r\n\
+-------------+------------+------------+------------+\r\n";
#endif

#if !defined MICO_FLASH_FOR_UPDATE && !defined MICO_FLASH_FOR_DRIVER
char MEMMAP[] = "\r\n\
+******************** MICO Flash Map *****************+\r\n\
+-- Content --+-- Flash ---+--- Start ---+--- End ----+\r\n\
| Bootloader  | %8s | 0x%08x | 0x%08x |\r\n\
| Settings    | %8s | 0x%08x | 0x%08x |\r\n\
| Application | %8s | 0x%08x | 0x%08x |\r\n\
+-------------+----------+------------+------------+\r\n";
#endif



char FileName[FILE_NAME_LENGTH];
char ERROR_STR [] = "\n\r*** ERROR: %s\n\r";    /* ERROR message string in code   */

extern char menu[];
extern void getline (char *line, int n);          /* input line               */
extern void startApplication(void);

/* Private function prototypes -----------------------------------------------*/
void SerialDownload(mico_flash_t flash, uint32_t flashdestination, int32_t maxRecvSize);
void SerialUpload(mico_flash_t flash, uint32_t flashdestination, char * fileName, int32_t maxRecvSize);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Analyse a command parameter
  * @param  commandBody: command string address
  * @param  para: The para we are looking for
  * @param  paraBody: A pointer to the buffer to receive the para body.
  * @param  paraBodyLength: The length, in bytes, of the buffer pointed to by the paraBody parameter.
  * @retval the actual length of the paraBody received, -1 means failed to find this paras 
  */
int findCommandPara(char *commandBody, char *para, char *paraBody, int paraBodyLength)
{
  int i = 0;
  int k, j;
  int retval = -1;
  char para_in_ram[100];
  strncpy(para_in_ram, para, 100);
  
  for (i = 0; para_in_ram[i] != 0; i++)  {                /* convert to upper characters */
    para_in_ram[i] = toupper(para_in_ram[i]);
  }

  i = 0;
  while(commandBody[i] != 0) {
    if(commandBody[i] == '-' ){
      for(j=i+1, k=0; *(para_in_ram+k)!=0x0; j++, k++ ){
        if(commandBody[j] != *(para_in_ram+k)){
          break;
        } 
      }

      if(*(para+k)!=0x0 || (commandBody[j]!=' '&& commandBody[j]!=0x0)){   /* para not found!             */
        i++;
        continue;
      }

      retval = 0;
      for (k = j+1; commandBody[k] == ' '; k++);      /* skip blanks                 */
      for(j = 0; commandBody[k] != ' ' && commandBody[k] != 0 && commandBody[k] != '-'; j++, k++){   /* para body found!             */
        if(paraBody) paraBody[j] = commandBody[k];
        retval ++;
        if( retval == paraBodyLength) goto exit;
      }
      goto exit;
    }
    i++;
  }

exit:
  if(paraBody) paraBody[retval] = 0x0;
  return retval;
}


/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval None
  */
void SerialDownload(mico_flash_t flash, uint32_t flashdestination, int32_t maxRecvSize)
{
  char Number[10] = "          ";
  int32_t Size = 0;

  printf("Waiting for the file to be sent ... (press 'a' to abort)\n\r");
  Size = Ymodem_Receive(&tab_1024[0], flash, flashdestination, maxRecvSize);
  if (Size > 0)
  {
    printf("\n\n\r Programming Successfully!\n\r\r\n Name: ");
    printf("%s", FileName);
    
    Int2Str((uint8_t *)Number, Size);
    printf("\n\r Size: ");
    printf("%s", Number);
    printf(" Bytes\r\n");
  }
  else if (Size == -1)
  {
    printf("\n\n\rThe image size is higher than memory!\n\r");
  }
  else if (Size == -2)
  {
    printf("\n\n\rVerification failed!\n\r");
  }
  else if (Size == -3)
  {
    printf("\r\n\nAborted by user.\n\r");
  }
  else
  {
    printf("\n\rFailed to receive file!\n\r");
  }
}

/**
  * @brief  Upload a file via serial port.
  * @param  None
  * @retval None
  */
void SerialUpload(mico_flash_t flash, uint32_t flashdestination, char *fileName, int32_t maxRecvSize)
{
  uint8_t status = 0;
  uint8_t key;

  printf("Select Receive File\n\r");
  MicoUartRecv( STDIO_UART, &key, 1, MICO_NEVER_TIMEOUT );

  if (key == CRC16)
  {
    /* Transmit the flash image through ymodem protocol */
    status = Ymodem_Transmit(flash, flashdestination, (uint8_t *)fileName, maxRecvSize);

    if (status != 0)
    {
      printf("\n\rError Occurred while Transmitting File\n\r");
    }
    else
    {
      printf("\n\rFile uploaded successfully \n\r");
    }
  }
}

/**
  * @brief  Display the Main Menu on HyperTerminal
  * @param  None
  * @retval None
  */
void Main_Menu(void)
{
  char cmdbuf [CMD_STRING_SIZE] = {0}, cmdname[15] = {0};     /* command input buffer        */
  int i, j;                                       /* index for command buffer    */
  int targetFlash;
  char startAddressStr[10], endAddressStr[10];
  int32_t startAddress, endAddress;
  bool inputFlashArea = false;

  while (1)  {                                    /* loop forever                */
    printf ("\nWiFiMCU> ");
    getline (&cmdbuf[0], sizeof (cmdbuf));        /* input command line          */

    for (i = 0; cmdbuf[i] == ' '; i++);           /* skip blanks on head         */
    for (; cmdbuf[i] != 0; i++)  {                /* convert to upper characters */
      cmdbuf[i] = toupper(cmdbuf[i]);
    }

    for (i = 0; cmdbuf[i] == ' '; i++);        /* skip blanks on head         */
    for(j=0; cmdbuf[i] != ' '&&cmdbuf[i] != 0; i++,j++)  {         /* find command name       */
      cmdname[j] = cmdbuf[i];
    }
    cmdname[j] = '\0';

    /***************** Command "0" or "BOOTUPDATE": Update the application  *************************/
    if(strcmp(cmdname, "BOOTUPDATE") == 0 || strcmp(cmdname, "0") == 0) {
      if (findCommandPara(cmdbuf, "r", NULL, 0) != -1){
        printf ("\n\rRead Bootloader only...\n\r");
        MicoFlashInitialize(MICO_FLASH_FOR_BOOT);
        SerialUpload(MICO_FLASH_FOR_BOOT, BOOT_START_ADDRESS, "BootLoaderImage.bin", BOOT_FLASH_SIZE);
        MicoFlashFinalize(MICO_FLASH_FOR_BOOT);
        continue;
      }
      printf ("\n\rUpdating Bootloader...\n\r");
      SerialDownload(MICO_FLASH_FOR_BOOT, BOOT_START_ADDRESS, BOOT_FLASH_SIZE);
    }

    /***************** Command "1" or "FWUPDATE": Update the MICO application  *************************/
    else if(strcmp(cmdname, "FWUPDATE") == 0 || strcmp(cmdname, "1") == 0)	{
      if (findCommandPara(cmdbuf, "r", NULL, 0) != -1){
        printf ("\n\rRead MICO application only...\n\r");
        MicoFlashInitialize(MICO_FLASH_FOR_APPLICATION);
        SerialUpload(MICO_FLASH_FOR_APPLICATION, APPLICATION_START_ADDRESS, "ApplicationImage.bin", APPLICATION_FLASH_SIZE);
        MicoFlashFinalize(MICO_FLASH_FOR_APPLICATION);
        continue;
      }
      printf ("\n\rUpdating MICO application...\n\r");
      SerialDownload(MICO_FLASH_FOR_APPLICATION, APPLICATION_START_ADDRESS, APPLICATION_FLASH_SIZE); 							   	
    }

    /***************** Command "2" or "DRIVERUPDATE": Update the RF driver  *************************/

    else if(strcmp(cmdname, "DRIVERUPDATE") == 0 || strcmp(cmdname, "2") == 0) {
#ifdef MICO_FLASH_FOR_DRIVER
      if (findCommandPara(cmdbuf, "r", NULL, 0) != -1){
        printf ("\n\rRead RF driver only...\n\r");
        MicoFlashInitialize(MICO_FLASH_FOR_DRIVER);
        SerialUpload(MICO_FLASH_FOR_DRIVER, DRIVER_START_ADDRESS, "DriverImage.bin", DRIVER_FLASH_SIZE);
        MicoFlashFinalize(MICO_FLASH_FOR_DRIVER);
        continue;
      }
      printf ("\n\rUpdating RF driver...\n\r");
      SerialDownload(MICO_FLASH_FOR_DRIVER, DRIVER_START_ADDRESS, DRIVER_FLASH_SIZE);  
#else
      printf ("\n\rNo independ flash memory for RF driver, exiting...\n\r");
#endif
    }

    /***************** Command "3" or "PARAUPDATE": Update the application  *************************/
    else if(strcmp(cmdname, "PARAUPDATE") == 0 || strcmp(cmdname, "3") == 0)  {
      if (findCommandPara(cmdbuf, "e", NULL, 0) != -1){
        printf ("\n\rErasing MICO settings only...\n\r");
        MicoFlashInitialize(MICO_FLASH_FOR_PARA);
        MicoFlashErase(MICO_FLASH_FOR_PARA, PARA_START_ADDRESS, PARA_END_ADDRESS);
        MicoFlashFinalize(MICO_FLASH_FOR_PARA);
        continue;
      }
      if (findCommandPara(cmdbuf, "r", NULL, 0) != -1){
        printf ("\n\rRead MICO settings only...\n\r");
        MicoFlashInitialize(MICO_FLASH_FOR_PARA);
        SerialUpload(MICO_FLASH_FOR_PARA, PARA_START_ADDRESS, "DriverImage.bin", PARA_FLASH_SIZE);
        MicoFlashFinalize(MICO_FLASH_FOR_PARA);
        continue;
      }
      printf ("\n\rUpdating MICO settings...\n\r");
      SerialDownload(MICO_FLASH_FOR_PARA, PARA_START_ADDRESS, PARA_FLASH_SIZE);                        
    }

    /***************** Command "4" or "FLASHUPDATE": : Update the Flash  *************************/
    else if(strcmp(cmdname, "FLASHUPDATE") == 0 || strcmp(cmdname, "4") == 0) {
      if (findCommandPara(cmdbuf, "i", NULL, 0) != -1){
        targetFlash = MICO_INTERNAL_FLASH;
      }else if(findCommandPara(cmdbuf, "s", NULL, 200) != -1){
        targetFlash = MICO_SPI_FLASH;
      }else{
        printf ("\n\rUnkown target type! Exiting...\n\r");
        continue;
      }

      inputFlashArea = false;
      if (findCommandPara(cmdbuf, "start", startAddressStr, 10) != -1){
        if(Str2Int((uint8_t *)startAddressStr, &startAddress)==0){ //Found Flash start address
          printf ("\n\rIllegal start address.\n\r");
          continue;
        }else{
          if (findCommandPara(cmdbuf, "end", endAddressStr, 10) != -1){ //Found Flash end address
            if(Str2Int((uint8_t *)endAddressStr, &endAddress)==0){
              printf ("\n\rIllegal end address.\n\r");
              continue;
            }else{
              inputFlashArea = true;
            }
          }else{
            printf ("\n\rFlash end address not found.\n\r");
            continue;
          }
        }
      }

      if(endAddress<startAddress && inputFlashArea == true) {
        printf ("\n\rIllegal flash address.\n\r");
        continue;
      }

      if(inputFlashArea != true){
        if(targetFlash == MICO_INTERNAL_FLASH){
          startAddress = platform_flash_peripherals[MICO_INTERNAL_FLASH].flash_start_addr ;
          endAddress = platform_flash_peripherals[MICO_INTERNAL_FLASH].flash_start_addr 
                     + platform_flash_peripherals[MICO_INTERNAL_FLASH].flash_length - 1;
        }else{
#ifdef USE_MICO_SPI_FLASH        
          startAddress = platform_flash_peripherals[MICO_SPI_FLASH].flash_start_addr ;
          endAddress = platform_flash_peripherals[MICO_SPI_FLASH].flash_start_addr 
                     + platform_flash_peripherals[MICO_SPI_FLASH].flash_length - 1;
#else
          printf ("\n\rSPI Flash not exist\n\r");
          continue;
#endif
        }
      }

      if (findCommandPara(cmdbuf, "e", NULL, 0) != -1){
        printf ("\n\rErasing flash content From 0x%x to 0x%x\n\r", startAddress, endAddress);
        MicoFlashInitialize((mico_flash_t)targetFlash);
        MicoFlashErase((mico_flash_t)targetFlash, startAddress, endAddress);
        MicoFlashFinalize((mico_flash_t)targetFlash);
        continue;
      }

      if (findCommandPara(cmdbuf, "r", NULL, 0) != -1){
        printf ("\n\rRead flash content From 0x%x to 0x%x\n\r", startAddress, endAddress);
        MicoFlashInitialize((mico_flash_t)targetFlash);
        SerialUpload((mico_flash_t)targetFlash, startAddress, "FlashImage.bin", endAddress-startAddress+1);
        MicoFlashFinalize((mico_flash_t)targetFlash);
        continue;
      }

      printf ("\n\rUpdating flash content From 0x%x to 0x%x\n\r", startAddress, endAddress);
      SerialDownload((mico_flash_t)targetFlash, startAddress, endAddress-startAddress+1);                           
    }

    /***************** Command: Reboot *************************/
    else if(strcmp(cmdname, "MEMORYMAP") == 0 || strcmp(cmdname, "5") == 0)  {
#if defined MICO_FLASH_FOR_UPDATE && defined MICO_FLASH_FOR_DRIVER
      printf(MEMMAP, flash_name[MICO_FLASH_FOR_BOOT],BOOT_START_ADDRESS,BOOT_END_ADDRESS,\
                     flash_name[MICO_FLASH_FOR_PARA], PARA_START_ADDRESS, PARA_END_ADDRESS,\
                     flash_name[MICO_FLASH_FOR_APPLICATION], APPLICATION_START_ADDRESS, APPLICATION_END_ADDRESS,\
                     flash_name[MICO_FLASH_FOR_UPDATE], UPDATE_START_ADDRESS, UPDATE_END_ADDRESS,\
                     flash_name[MICO_FLASH_FOR_DRIVER], DRIVER_START_ADDRESS, DRIVER_END_ADDRESS);
#endif
#if !defined MICO_FLASH_FOR_UPDATE && defined MICO_FLASH_FOR_DRIVER
      printf(MEMMAP, flash_name[MICO_FLASH_FOR_BOOT],BOOT_START_ADDRESS,BOOT_END_ADDRESS,\
                     flash_name[MICO_FLASH_FOR_PARA], PARA_START_ADDRESS, PARA_END_ADDRESS,\
                     flash_name[MICO_FLASH_FOR_APPLICATION], APPLICATION_START_ADDRESS, APPLICATION_END_ADDRESS,\
                     flash_name[MICO_FLASH_FOR_DRIVER], DRIVER_START_ADDRESS, DRIVER_END_ADDRESS);
#endif
#if defined MICO_FLASH_FOR_UPDATE && !defined MICO_FLASH_FOR_DRIVER
      printf(MEMMAP, flash_name[MICO_FLASH_FOR_BOOT],BOOT_START_ADDRESS,BOOT_END_ADDRESS,\
                     flash_name[MICO_FLASH_FOR_PARA], PARA_START_ADDRESS, PARA_END_ADDRESS,\
                     flash_name[MICO_FLASH_FOR_APPLICATION], APPLICATION_START_ADDRESS, APPLICATION_END_ADDRESS);
#endif
#if !defined MICO_FLASH_FOR_UPDATE && !defined MICO_FLASH_FOR_DRIVER
      printf(MEMMAP, flash_name[MICO_FLASH_FOR_BOOT],BOOT_START_ADDRESS,BOOT_END_ADDRESS,\
                     flash_name[MICO_FLASH_FOR_PARA], PARA_START_ADDRESS, PARA_END_ADDRESS,\
                     flash_name[MICO_FLASH_FOR_APPLICATION], APPLICATION_START_ADDRESS, APPLICATION_END_ADDRESS);
#endif 
    }
    /***************** Command: Excute the application *************************/
    else if(strcmp(cmdname, "BOOT") == 0 || strcmp(cmdname, "6") == 0)	{
      printf ("\n\rBooting.......\n\r");
      startApplication();
    }

   /***************** Command: Reboot *************************/
    else if(strcmp(cmdname, "REBOOT") == 0 || strcmp(cmdname, "7") == 0)  {
      printf ("\n\rReBooting.......\n\r");
      MicoSystemReboot();
    break;                              
  }

	else if(strcmp(cmdname, "HELP") == 0 || strcmp(cmdname, "?") == 0)	{
    printf ( menu, MODEL, Bootloader_REVISION );                       /* display command menu        */
		break;
	}

	else if(strcmp(cmdname, "") == 0 )	{                         
		break;
	}
	else{
	    printf (ERROR_STR, "UNKNOWN COMMAND");
		break;
	}
  }
}
