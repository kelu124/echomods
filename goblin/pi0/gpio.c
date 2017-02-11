#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

// Code from http://d-fence.sytes.net/raspberry-pis-gpio-speed/
// to be tested now on a raspberry pi 0

static volatile uint32_t *gpio;

int main(int argc, char **argv)
{
	int fd;

	// Obtain handle to physical memory
	if ((fd = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0) {
		printf("Unable to open /dev/mem: %s\n", strerror(errno));
		return -1;
	}

	// map a page of memory to gpio at offset 0x20200000 which is where GPIO goodnessstarts
	gpio = (uint32_t *)mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x20200000);
	if (gpio == 0){
		printf("Mmap failed: %s\n", strerror(errno));
		return -1;
	}

	// set gpio17 as an output
	// increment the pointer to 0x20200004
	// set the value through a little bit twiddling where we only modify the bits 21-23 in the register
	*(gpio + 1) = (*(gpio + 1) & ~(7 << 21)) | (1 << 21);

  // Now do a loop as fast as possible in assembler
		__asm__("loop:\n\t"
            
            "mov r1,#1\n\t"			//PIN ON
            "lsl r1,#17\n\t"
            "str r1,[%0,#28]\n\t"
            
            "mov r1,#1\n\t"			//PIN OFF
            "lsl r1,#17\n\t"
            "str r1,[%0,#40]\n\t"

            "b loop\n\t"
            :
            :"r"((uint32_t)gpio)
            : "r0", "r1"
            );
}
