
USBMODE ?= 0
GPIOMODE ?= 0

ifeq ($(shell bash -c 'type -p icoprog'),)
SSH_RASPI ?= ssh pi@raspi
else
SSH_RASPI ?= sh -c
endif

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

example.blif: example.v
	yosys -p 'synth_ice40 -blif example.blif' example.v

example.asc: example.blif example.pcf
	arachne-pnr -d 8k -p example.pcf -o example.asc example.blif

example.bin: example.asc
	icetime -d hx8k -c 100 example.asc
	icepack example.asc example.bin

example_sram: example.bin
	$(SSH_RASPI) 'icoprog -p' < example.bin

example_flash: example.bin
	$(SSH_RASPI) 'icoprog -f' < example.bin
	$(SSH_RASPI) 'icoprog -b'

reset:
	$(SSH_RASPI) 'icoprog -f' < example.pcf
	$(SSH_RASPI) 'icoprog -b'

install: icoprog
	sudo install icoprog /usr/local/bin/
	sudo chmod u+s /usr/local/bin/icoprog

uninstall:
	sudo rm -f /usr/local/bin/icoprog

clean:
	rm -f icoprog example.blif example.asc example.bin

.PHONY: example_sram example_flash reset install clean

