---

layout: post

title: 2020-03-25 i2s seems to need to be RPi-mastered

---


-   curl https://get.pimoroni.com/phatdac | bash
-   https://learn.pimoroni.com/tutorial/phat/raspberry-pi-phat-dac-install
-   rpi-i2s-audio
-   echo 'my\_loader' | sudo tee --append /etc/modules &gt; /dev/null
-   Need to have a i2s master on RPi
-   https://github.com/PaulCreaser/rpi-i2s-audio.git
-   sudo rmmod snd\_soc\_hifiberry\_dacplus
-   sudo rmmod clk\_hifiberry\_dacpro
-   Others
-   https://github.com/AkiyukiOkayasu/RaspberryPi\_I2S\_Slave
-   https://github.com/taylorxv/raspberry-pi-i2s-driver

I send 2 channels. Into one channel always 0x3F into second channel
0x29. 0x7C is shifted byt 2 bits value 0x29F3.

