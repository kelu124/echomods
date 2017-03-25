#include "MICO.h"
#include "MICOSystemMonitor.h"
#include "MICONotificationCenter.h"
#include "adc.h"

#define adc_log(M, ...) custom_log("ADC", M, ##__VA_ARGS__)

static uint16_t buffer[Adc_BufferLength];
static mico_semaphore_t dataIsReady_semaphore;
static mico_semaphore_t dataIsCopied_semaphore;

mico_queue_t Adc_Data_queue;

void DMA2_Stream0_IRQHandler()
{ 
  /*
  // Used for conversion time measurement
  static uint32_t x = 0, y = 0;
  x = SysTick->LOAD;
  y = x - SysTick->VAL;
  */
  
  // Clear the interrupt flag
  DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
  
  // Restart the ADC
  ADC_ContinuousModeCmd(ADC1, DISABLE);
  ADC_ContinuousModeCmd(ADC1, ENABLE);
  
  // Clear the overflow bit
  ADC_ClearITPendingBit(ADC1, ADC_IT_OVR);
  
  // Restart the DMA
  DMA_SetCurrDataCounter(DMA2_Stream0, Adc_BufferLength);
  DMA_Cmd(DMA2_Stream0, ENABLE);

  // If data has not been copied yet
  if (mico_rtos_get_semaphore(&dataIsCopied_semaphore, 0) != kNoErr)
  {
    adc_log("The buffer has not been copied to the queue");
  }
  
  else
  {
    // Send a signal that data is ready
    mico_rtos_set_semaphore(&dataIsReady_semaphore);
  }
}


static void CopyToQueue_thread(void *arg)
{
  mico_rtos_set_semaphore(&dataIsCopied_semaphore);
  
  while(1)
  {
    // Wait until data is received
    if (mico_rtos_get_semaphore(&dataIsReady_semaphore, 10000) == kNoErr)
    {
      // Put data into the queue
      if (!mico_rtos_is_queue_full(&Adc_Data_queue))
      {
        mico_rtos_push_to_queue(&Adc_Data_queue, buffer, 0);
        mico_rtos_set_semaphore(&dataIsCopied_semaphore);
      }
      
      // If the queue is full
      else
      {
        adc_log("Queue for ADC data is full");
      }
    }
  }
}


void Adc_Start()
{
  /*
  // Used for conversion time measurement
  SysTick->VAL = 0;
  ADC_SoftwareStartConv(ADC1);
  */
  
  TIM_SetCounter(TIM3, 0);
  TIM_Cmd(TIM3, ENABLE);
  adc_log("ADC is working now");
}

void Adc_Stop()
{
  TIM_Cmd(TIM3, DISABLE);
  adc_log("ADC is stopped now");
}

void Adc_Init()
{
  RCC_ClocksTypeDef clocks;
  GPIO_InitTypeDef gpio;
  DMA_InitTypeDef dma;
  ADC_InitTypeDef adc;
  ADC_CommonInitTypeDef adcCommon;
  
  // Get info about the system clocks
  RCC_GetClocksFreq(&clocks);
  
  // Enable clock for required peripherals
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /*
  * Timer configuration
  */
  
  // Config the timer to count evert 0.1 ms
  // Update event will occur every Adc_MeasurementPeriod ms
  TIM_TimeBaseInitTypeDef timer;
  timer.TIM_ClockDivision = TIM_CKD_DIV1;
  timer.TIM_CounterMode = TIM_CounterMode_Down;
  timer.TIM_Period = 10 * Adc_MeasurementPeriod - 1;
  timer.TIM_Prescaler = 2 * clocks.PCLK1_Frequency / 10000 - 1;
  TIM_TimeBaseInit(TIM3, &timer);
  
  // Enable sycronization output
  TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
  
  /*
  * GPIO configuration
  */
  
  // Configure the ADC input pin
  gpio.GPIO_Pin = GPIO_Pin_1;
  gpio.GPIO_Mode = GPIO_Mode_AN;
  gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &gpio);

  /*
  * DMA configuration
  */
  
  // Configure the DMA
  DMA_DeInit(DMA2_Stream0);
  DMA_StructInit(&dma);
  dma.DMA_Channel = DMA_Channel_0;
  dma.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
  dma.DMA_Memory0BaseAddr = (uint32_t)buffer;
  dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
  dma.DMA_BufferSize = Adc_BufferLength;
  dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
  dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  dma.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  dma.DMA_Mode = DMA_Mode_Normal;
  dma.DMA_Priority = DMA_Priority_VeryHigh;
  dma.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  dma.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  dma.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &dma);
  DMA_Cmd(DMA2_Stream0, ENABLE);
  
  // Enable DMA interrupt
  DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);
  NVIC_EnableIRQ(DMA2_Stream0_IRQn);

  /*
  * ADC configuration
  */
  
  ADC_DeInit();
  
  // Config the ADC
  adcCommon.ADC_Mode = ADC_Mode_Independent;
  adcCommon.ADC_Prescaler = ADC_Prescaler_Div4;
  adcCommon.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  adcCommon.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&adcCommon);

  // Keep ADC configuring
  adc.ADC_ScanConvMode = DISABLE;
  adc.ADC_ContinuousConvMode = ENABLE;
  adc.ADC_DataAlign = ADC_DataAlign_Right;
  adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
  adc.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
  adc.ADC_NbrOfConversion = 1;
  adc.ADC_Resolution = ADC_Resolution_12b;
  ADC_Init(ADC1, &adc);
  
  // Choose the channel
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_3Cycles);

  // Enable DMA request
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
  ADC_DMACmd(ADC1, ENABLE);
  
  // Enable the ADC
  ADC_Cmd(ADC1, ENABLE);
  
  /*
  * Other configurations
  */
  
  // Init a semaphore for signalig about data readiness
  mico_rtos_init_semaphore(&dataIsReady_semaphore, 1);
  
  // Init a semaphore for signalig about copying completion
  mico_rtos_init_semaphore(&dataIsCopied_semaphore, 1);
  
  // Init queue for adc data
  mico_rtos_init_queue(&Adc_Data_queue, "ADC Data", sizeof(buffer), Adc_QueueLength);
  
  // Create a thread for data copying
  mico_rtos_create_thread(NULL, MICO_APPLICATION_PRIORITY, "Copy to queue", CopyToQueue_thread, 256, NULL);
}

