#include <libmaple/dac.h>
// Code published at https://gist.github.com/kelu124/fa014ae6c96b7006268d37c72aa64bf7
// Question raised at https://forums.adafruit.com/viewtopic.php?f=57&t=100553&p=503227&hilit=DAC+feather+wiced#p503227

const int ledPin = PA15;
pinMode(ledPin, PWM);  // setup the pin as PWM
const int DAC_CH1 = 1;

void setup() 
{
  dac_enable_channel(DAC, 1); // Configures Pin A4 as DAC1
  dac_init(DAC, DAC_CH1 | DAC_CH2);     // Start DAC1
}

void loop() 
{
  uint32_t i = 0;
  for ( i=0; i<4096; i++ )
  {
    dac_write_channel(DAC, DAC_CH1, i);
  }  
  for ( i=4095; i>0; i-- )
  {
    dac_write_channel(DAC, DAC_CH1, i);
    pwmWrite(ledPin, 16*i);
  }  
}
