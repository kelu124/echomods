/**
******************************************************************************
* @file    Getline.c 
* @author  William Xu
* @version V2.0.0
* @date    05-Oct-2014
* @brief   Line Edited Character Input
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

#include <stdio.h>
#include "common.h"                     /* global project definition file   */
#include "Mico.h"
#include "platform_config.h"
#include "MicoPlatform.h"

#define CNTLQ      0x11
#define CNTLS      0x13
#define DEL        0x7F
#define BACKSPACE  0x08
#define CR         0x0D
#define LF         0x0A

/***************/
/* Line Editor */
/***************/
void getline (char *line, int n)  {
  int  cnt = 0;
  char c;

  do  {
    MicoUartRecv( STDIO_UART, &c, 1, MICO_NEVER_TIMEOUT );
    if (c == CR)  c = LF;     /* read character                 */
    if (c == BACKSPACE  ||  c == DEL)  {    /* process backspace              */
      if (cnt != 0)  {
        cnt--;                              /* decrement count                */
        line--;                             /* and line pointer               */
        putchar (BACKSPACE);                /* echo backspace                 */
        putchar (' ');
        putchar (BACKSPACE);
      }
    }
    else if (c != CNTLQ && c != CNTLS)  {   /* ignore Control S/Q             */
      putchar (*line = c);                  /* echo and store character       */
      line++;                               /* increment line pointer         */
      cnt++;                                /* and count                      */
    }
  }  while (cnt < n - 1  &&  c != LF);      /* check limit and line feed      */
  *(line - 1) = 0;                          /* mark end of string             */
}

#ifdef MICO_ENABLE_STDIO_TO_BOOT
int stdio_break_in(void)
{
    uint8_t c;
    int i, j;
    
    for(i=0, j=0;i<10;i++) {
      if (kNoErr != MicoUartRecv( STDIO_UART, &c, 1, 10)) 
        continue;

      if (c == 0x20) {
        j++;
        if (j > 5)
          return 1; 
      } else {
        j = 0;
      }
    }

    return 0;
}
#endif

