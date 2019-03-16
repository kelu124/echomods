
USBMODE ?= 0
GPIOMODE ?= 0

ifeq ($(USBMODE),1)
icoprog: icoprog.cc
	gcc -o icoprog -Wall -Os icoprog.cc -D USBMODE -lftdi -lrt -lstdc++
else
ifeq ($(GPIOMODE),1)
icoprog: icoprog.cc
	gcc -o icoprog -Wall -Os icoprog.cc -D GPIOMODE -lrt -lstdc++
else
icoprog: icoprog.cc
	gcc -o icoprog -Wall -Os icoprog.cc -lwiringPi -lrt -lstdc++
endif
endif

blink: example.bin
	$(SSH_RASPI) 'icoprog -p' < BLINK.bin

install: icoprog
	sudo install icoprog /usr/local/bin/
	sudo chmod u+s /usr/local/bin/icoprog

uninstall:
	sudo rm -f /usr/local/bin/icoprog

clean:
	rm -f icoprog example.blif example.asc example.bin


