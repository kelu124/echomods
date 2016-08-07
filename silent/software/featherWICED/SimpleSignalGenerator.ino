#include <libmaple/dac.h>

/*
Quick signal emulator for Feather
70us period
*/

uint32_t i = 0;
  
void setup() 
{
  dac_enable_channel(DAC, 1); // Configures Pin A4 as DAC1
  dac_init(DAC, DAC_CH1);     // Start DAC1
  dac_write_channel(DAC, DAC_CH1, 256);
}

void loop() 
{
/*
We get 128 periods (256+i followed by 256-i) in 70us, that's 1.8 periods per us, so a "slow" signal at nearly 2MHz. 
200mV +-100mV
*/
  uint32_t i = 0;
  for ( i=128; i>0; i-- )
  {
    dac_write_channel(DAC, DAC_CH1, 256+i);
    dac_write_channel(DAC, DAC_CH1, 256-i);
  }  
  dac_write_channel(DAC, DAC_CH1, 256);
}
