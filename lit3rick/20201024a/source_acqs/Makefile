
USBMODE ?= 0
GPIOMODE ?= 0

ifeq ($(shell bash -c 'type -p lit3prog'),)
SSH_RASPI ?= ssh pi@raspi
else
SSH_RASPI ?= sh -c
endif

ifeq ($(USBMODE),1)
lit3prog: lit3prog.cc
	gcc -o lit3prog -Wall -Os lit3prog.cc -D USBMODE -lftdi -lrt -lstdc++
else
ifeq ($(GPIOMODE),1)
lit3prog: lit3prog.cc
	gcc -o lit3prog -Wall -Os lit3prog.cc -D GPIOMODE -lrt -lstdc++
else
lit3prog: lit3prog.cc
	gcc -o lit3prog -Wall -Os lit3prog.cc -lwiringPi -lrt -lstdc++
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
	$(SSH_RASPI) 'lit3prog -p' < example.bin

example_flash: example.bin
	$(SSH_RASPI) 'lit3prog -f' < example.bin
	$(SSH_RASPI) 'lit3prog -b'

reset:
	$(SSH_RASPI) 'lit3prog -f' < example.pcf
	$(SSH_RASPI) 'lit3prog -b'

install: lit3prog
	sudo install lit3prog /usr/local/bin/
	sudo chmod u+s /usr/local/bin/lit3prog

uninstall:
	sudo rm -f /usr/local/bin/lit3prog

clean:
	rm -f lit3prog example.blif example.asc example.bin

.PHONY: example_sram example_flash reset install clean

