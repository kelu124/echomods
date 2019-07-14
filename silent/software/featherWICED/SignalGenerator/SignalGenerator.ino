/*
	Author: Kelu124
	Copyright 2016
	Repo:https://github.com/kelu124/echomods/tree/master/silent
	Description: Quick signal emulator for Feather. 70us period. DAC runs at 2MHz
	Licence: GNU GPL 2

*/

#include <libmaple/dac.h>

/*
  Quick signal emulator for Feather
  70us period
*/

const int  thisLED_PIN = PA15;
const int  TRIG_PIN = PB5;
uint32_t i = 0;

void emulator() {

  digitalWrite(thisLED_PIN, HIGH);
  
  uint32_t i = 0;
  uint32_t j = 0;

  dac_write_channel(DAC, DAC_CH1, 256 + 32);
  dac_write_channel(DAC, DAC_CH1, 256 - 32);

  for ( i = 128; i > 0; i-- )
  {
    dac_write_channel(DAC, DAC_CH1, 256 + i);
    dac_write_channel(DAC, DAC_CH1, 256 - i);
  }
  /* Some space */
  for ( j = 40; j > 0; j-- )
  {
    dac_write_channel(DAC, DAC_CH1, 256);
  }

  dac_write_channel(DAC, DAC_CH1, 256 + 128);
  dac_write_channel(DAC, DAC_CH1, 256 - 128);

  for ( j = 20; j > 0; j-- )
  {
    dac_write_channel(DAC, DAC_CH1, 256);
  }

  dac_write_channel(DAC, DAC_CH1, 256 + 64);
  dac_write_channel(DAC, DAC_CH1, 256 - 64);
  dac_write_channel(DAC, DAC_CH1, 256 + 64);
  dac_write_channel(DAC, DAC_CH1, 256 - 64);

  for ( j = 20; j > 0; j-- )
  {
    dac_write_channel(DAC, DAC_CH1, 256);
  }

  dac_write_channel(DAC, DAC_CH1, 256 + 32);
  dac_write_channel(DAC, DAC_CH1, 256 - 32);
  dac_write_channel(DAC, DAC_CH1, 256 + 32);
  dac_write_channel(DAC, DAC_CH1, 256 - 32);
  dac_write_channel(DAC, DAC_CH1, 256 + 32);
  dac_write_channel(DAC, DAC_CH1, 256 - 32);

  for ( j = 10; j > 0; j-- )
  {
    dac_write_channel(DAC, DAC_CH1, 256);
  }

  dac_write_channel(DAC, DAC_CH1, 256 + 16);
  dac_write_channel(DAC, DAC_CH1, 256 - 16);

  for ( j = 10; j > 0; j-- )
  {
    dac_write_channel(DAC, DAC_CH1, 256);
  }

  dac_write_channel(DAC, DAC_CH1, 256 + 8);
  dac_write_channel(DAC, DAC_CH1, 256 - 8);

  for ( j = 10; j > 0; j-- )
  {
    dac_write_channel(DAC, DAC_CH1, 256);
  }

  dac_write_channel(DAC, DAC_CH1, 256 + 4);
  dac_write_channel(DAC, DAC_CH1, 256 - 4);

  for ( j = 10; j > 0; j-- )
  {
    dac_write_channel(DAC, DAC_CH1, 256);
  }

  dac_write_channel(DAC, DAC_CH1, 256 + 2);
  dac_write_channel(DAC, DAC_CH1, 256 - 2);

  for ( j = 10; j > 0; j-- )
  {
    dac_write_channel(DAC, DAC_CH1, 256);
  }

  dac_write_channel(DAC, DAC_CH1, 256 + 16);
  dac_write_channel(DAC, DAC_CH1, 256 - 16);
  
  for ( j = 20; j > 0; j-- )
  {
    dac_write_channel(DAC, DAC_CH1, 256);
  }

  digitalWrite(thisLED_PIN, LOW);
  
}

void setup()
{
  dac_enable_channel(DAC, 1); // Configures Pin A4 as DAC1
  dac_init(DAC, DAC_CH1);     // Start DAC1
  dac_write_channel(DAC, DAC_CH1, 256);

  pinMode(TRIG_PIN, INPUT_PULLDOWN);
  attachInterrupt(TRIG_PIN, emulator, RISING);

}

void loop()
{
  /*
    We get 128 periods (256+i followed by 256-i) in 70us, that's 1.8 periods per us, so a "slow" signal at nearly 2MHz.
  */

}
