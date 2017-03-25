/**
******************************************************************************
* @file    MICOSystemMonitor.c 
* @author  William Xu
* @version V1.0.0
* @date    05-May-2014
* @brief   System monitor function, create a system monitor thread, and user 
*          can add own monitor events.
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

#include "MICO.h"
#include "MicoSystemMonitor.h"
#include "MicoPlatform.h"



#define DEFAULT_SYSTEM_MONITOR_PERIOD   (2000)

#ifndef MAXIMUM_NUMBER_OF_SYSTEM_MONITORS
#define MAXIMUM_NUMBER_OF_SYSTEM_MONITORS    (5)
#endif

static mico_system_monitor_t* system_monitors[MAXIMUM_NUMBER_OF_SYSTEM_MONITORS];
void mico_system_monitor_thread_main( void* arg );

OSStatus MICOStartSystemMonitor ( mico_Context_t * const inContext )
{
  OSStatus err = kNoErr;
  require_noerr(MicoWdgInitialize( DEFAULT_SYSTEM_MONITOR_PERIOD + 1000 ), exit);
  memset(system_monitors, 0, sizeof(system_monitors));

  err = mico_rtos_create_thread(NULL, 0, "SYS MONITOR", mico_system_monitor_thread_main, STACK_SIZE_MICO_SYSTEM_MONITOR_THREAD, (void*)inContext );
  require_noerr(err, exit);
exit:
  return err;
}

void mico_system_monitor_thread_main( void* arg )
{
  (void)arg;
  
  while (1)
  {
    int a;
    uint32_t current_time = mico_get_time();
    
    for (a = 0; a < MAXIMUM_NUMBER_OF_SYSTEM_MONITORS; ++a)
    {
      if (system_monitors[a] != NULL)
      {
        if ((current_time - system_monitors[a]->last_update) > system_monitors[a]->longest_permitted_delay)
        {
          /* A system monitor update period has been missed */
          while(1);
        }
      }
    }
    
    MicoWdgReload();
    mico_thread_msleep(DEFAULT_SYSTEM_MONITOR_PERIOD);
  }
}

OSStatus MICORegisterSystemMonitor(mico_system_monitor_t* system_monitor, uint32_t initial_permitted_delay)
{
  int a;
  
  /* Find spare entry and add the new system monitor */
  for ( a = 0; a < MAXIMUM_NUMBER_OF_SYSTEM_MONITORS; ++a )
  {
    if (system_monitors[a] == NULL)
    {
      system_monitor->last_update = mico_get_time();
      system_monitor->longest_permitted_delay = initial_permitted_delay;
      system_monitors[a] = system_monitor;
      return kNoErr;
    }
  }
  
  return kUnknownErr;
}

OSStatus MICOUpdateSystemMonitor(mico_system_monitor_t* system_monitor, uint32_t permitted_delay)
{
  uint32_t current_time = mico_get_time();
  /* Update the system monitor if it hasn't already passed it's permitted delay */
  if ((current_time - system_monitor->last_update) <= system_monitor->longest_permitted_delay)
  {
    system_monitor->last_update             = current_time;
    system_monitor->longest_permitted_delay = permitted_delay;
  }
  
  return kNoErr;
}
