/***
 * File: patch_keil.c
 * porting iar project to keil, something need to do.
 *
 * Created by JerryYu @ Jan 13rd,2015
 * Ver: 0.1
 * */
#include "Common.h"
#include "MicoDefaults.h"
#include "MicoRTOS.h"

#ifndef  NO_MICO_RTOS
USED int _mutex_initialize(void* mutex)
{
  return 1;
}

USED void _mutex_acquire(void* mutex)
{
  mico_rtos_suspend_all_thread();
}

USED void _mutex_release(void* mutex)
{
  mico_rtos_resume_all_thread();
}

USED void _mutex_free(void* mutex)
{
}
#endif

