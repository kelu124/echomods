/**
******************************************************************************
* @file    BootloaderEntrance.c 
* @author  William Xu
* @version V2.0.0
* @date    05-Oct-2014
* @brief   MICO bootloader main entrance.
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


#include "Mico.h"
#include "MicoPlatform.h"
#include "platform.h"
#include "platformInternal.h"
#include "platform_config.h"

#define boot_log(M, ...) custom_log("BOOT", M, ##__VA_ARGS__)
#define boot_log_trace() custom_log_trace("BOOT")

extern void Main_Menu(void);
extern OSStatus update(void);

#ifdef SIZE_OPTIMIZE
char menu[] =
"\r\n"
"MICO Bootloader for %s, Bootloader Version: %s\r\n"
"0:BOOTUPDATE <-r>\r\n"
"1:FWUPDATE <-r>\r\n"
"2:DRIVERUPDATE <-r>\r\n"
"3:PARAUPDATE <-r><-e>\r\n"
"4:FLASHUPDATE  <-i><-s><-e><-r><-start><-end>\r\n"
"5:MEMORYMAP\r\n"
"6:BOOT\r\n"
"7:REBOOT\r\n";
#else
char menu[] =
"\r\n"
"WiFiMCU Bootloader for %s, Bootloader Version: %s\r\n"
"+ command -------------------------+ function ------------+\r\n"
"| 0:BOOTUPDATE    <-r>             | Update bootloader    |\r\n"
"| 1:FWUPDATE      <-r>             | Update application   |\r\n"
"| 2:DRIVERUPDATE  <-r>             | Update RF driver     |\r\n"
"| 3:PARAUPDATE    <-r><-e>         | Update MICO settings |\r\n"
"| 4:FLASHUPDATE   <-i><-s><-e><-r> |                      |\r\n"
"|    <-start address><-end address>| Update flash content |\r\n"
"| 5:MEMORYMAP                      | List flash memory map|\r\n"
"| 6:BOOT                           | Excute application   |\r\n"
"| 7:REBOOT                         | Reboot               |\r\n"
"+----------------------------------+----------------------+\r\n"
"|Modified by Doit Team, Pls visit www.doit.am for more info.|\r\n"
" Notes:\r\n"
" -e Erase only  -r Read from flash -i internal flash  -s SPI flash\r\n"
" -start flash start address -end flash start address\r\n"
" Example: Input \"4 -s -start 0x00002000 -end 0x0003FFFF\": Update spi\r\n"
"          flash from 0x00002000 to 0x0003FFFF\r\n";
#endif
#ifdef MICO_ENABLE_STDIO_TO_BOOT
extern int stdio_break_in(void);
#endif

int main(void)
{
  init_clocks();
  init_memory();
  init_architecture();
  init_platform_bootloader();

  mico_set_bootload_ver();
  
#ifdef MICO_FLASH_FOR_UPDATE
  update();
#endif

  if(MicoShouldEnterBootloader() == false)
    startApplication();
#if 0
#ifdef MICO_ENABLE_STDIO_TO_BOOT
  if (stdio_break_in() == 1)
    goto BOOT;
#endif
  if(MicoShouldEnterBootloader() == false)
    startApplication();
  else if(MicoShouldEnterMFGMode() == true)
    startApplication();
#ifdef MICO_ATE_START_ADDRESS
  else if (MicoShouldEnterATEMode()) {
    startATEApplication();
	}
#endif 
BOOT:
#endif
  
  printf ( menu, MODEL, Bootloader_REVISION );

  while(1){                             
    Main_Menu ();
  }
}


