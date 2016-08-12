#ifndef __ADC_H__
#define __ADC_H__

#define Adc_MeasurementPeriod 10
#define Adc_BufferLength 416
#define Adc_QueueLength 2

extern mico_queue_t Adc_Data_queue;

void Adc_Init();
void Adc_Start();
void Adc_Stop();

#endif