/*
 *  IcoProg -- Programmer and Debug Tool for the IcoBoard
 *
 *  Copyright (C) 2016  Clifford Wolf <clifford@clifford.at>
 *  
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <assert.h>
#include <vector>

bool verbose = false;
bool ftdi_verbose = false;
bool got_error = false;

bool enable_prog_port = false;
bool enable_data_port = false;

// --------------------------------------------------------------------------------------------

#if !defined(USBMODE) && !defined(GPIOMODE)

#  include <wiringPi.h>

#  define RPI_ICE_CLK     14 // GP11 -- 
#  define RPI_ICE_CDONE   16 // GP15 -- 
#  define RPI_ICE_MOSI    12 // GP10 --
#  define RPI_ICE_MISO    13 // GP09 -- 
#  define LOAD_FROM_FLASH 25 // IGNORE -- PIN 33, GPIO.23
#  define RPI_ICE_CRESET   6 // GP25 -- 
#  define RPI_ICE_CS      11 // GP07 -- 
#  define RPI_ICE_SELECT  24 // IGNORE --PIN 32, GPIO.26

#  define RASPI_D8   0 // PIN 11, GPIO.0
#  define RASPI_D7   1 // PIN 12, GPIO.1
#  define RASPI_D6   3 // PIN 15, GPIO.3
#  define RASPI_D5   4 // PIN 16, GPIO.4
#  define RASPI_D4  12 // PIN 19, MOSI
#  define RASPI_D3  13 // PIN 21, MISO
#  define RASPI_D2  11 // PIN 26, CE1
#  define RASPI_D1  24 // PIN 35, GPIO.24
#  define RASPI_D0  27 // PIN 36, GPIO.27
#  define RASPI_DIR 28 // PIN 38, GPIO.28
#  define RASPI_CLK 29 // PIN 40, GPIO.29

void digitalSync(int usec_delay)
{
	usleep(usec_delay);
}

#endif

// --------------------------------------------------------------------------------------------

#ifdef USBMODE

#  include <ftdi.h>

// ADBUS0  0     BDBUS0 16
// ADBUS1  1     BDBUS1 17
// ADBUS2  2     BDBUS2 18
// ADBUS3  3     BDBUS3 19
// ADBUS4  4     BDBUS4 20
// ADBUS5  5     BDBUS5 21
// ADBUS6  6     BDBUS6 22
// ADBUS7  7     BDBUS7 23
// ACBUS0  8     BCBUS0 24
// ACBUS1  9     BCBUS1 25
// ACBUS2 10     BCBUS2 26
// ACBUS3 11     BCBUS3 27
// ACBUS4 12     BCBUS4 28
// ACBUS5 13     BCBUS5 29
// ACBUS6 14     BCBUS6 30
// ACBUS7 15     BCBUS7 31

#  define RPI_ICE_CLK     16 // PIN  7
#  define RPI_ICE_CDONE   22 // PIN 13
#  define RPI_ICE_MOSI    17 // PIN 29
#  define RPI_ICE_MISO    18 // PIN 31
#  define LOAD_FROM_FLASH 21 // PIN 33
#  define RPI_ICE_CRESET  23 // PIN 37
#  define RPI_ICE_CS      20 // PIN 24
#  define RPI_ICE_SELECT  19 // PIN 32

#  define RASPI_D8  12 // PIN 11
#  define RASPI_D7  14 // PIN 12
#  define RASPI_D6   6 // PIN 15
#  define RASPI_D5   7 // PIN 16
#  define RASPI_D4   1 // PIN 19
#  define RASPI_D3   2 // PIN 21
#  define RASPI_D2  10 // PIN 26
#  define RASPI_D1   3 // PIN 35
#  define RASPI_D0  13 // PIN 36
#  define RASPI_DIR  4 // PIN 38
#  define RASPI_CLK  5 // PIN 40

#  define INPUT 0
#  define OUTPUT 1

#  define LOW 0
#  define HIGH 1

struct ftdi_context ftdia, ftdib;
uint32_t ftdistate_dir, ftdistate_val;

void my_ftdi_send(struct ftdi_context *ftdi, uint8_t *buffer, int len)
{
	char interface = ftdi == &ftdia ? 'A' : ftdi == &ftdib ? 'B' : 'X';

	if (ftdi_verbose) {
		printf("ftdi-send-%c>", interface);
		for (int i = 0; i < len; i++)
			printf(" %02x", buffer[i]);
		printf("\n");
	}

	while (len > 0) {
		int rc = ftdi_write_data(ftdi, buffer, len);
		if (rc <= 0) {
			fprintf(stderr, "Communication error. (ftdi interface %c write rc=%d, %s)\n",
					interface, rc, ftdi_get_error_string(ftdi));
			exit(1);
		}
		buffer += rc;
		len -= rc;
	}
}

void my_ftdi_recv(struct ftdi_context *ftdi, uint8_t *buffer, int len)
{
	char interface = ftdi == &ftdia ? 'A' : ftdi == &ftdib ? 'B' : 'X';

	int retry_cnt = 0;
	int offset = 0;

	while (offset < len)
	{
		int rc = ftdi_read_data(ftdi, buffer + offset, len - offset);

		if (rc == 0)
		{
			if (++retry_cnt > 10)
			{
				if (ftdi_verbose) {
					printf("ftdi-partial-recv-%c>", interface);
					for (int i = 0; i < offset; i++)
						printf(" %02x", buffer[i]);
					printf("\n");
				}
				fprintf(stderr, "FTDI interface %c read timeout after %d / %d bytes.\n",
						interface, offset, len);
				exit(1);
			}
			if (retry_cnt > 1)
				fprintf(stderr, "FTDI interface %c read timeout after %d / %d bytes, keep waiting..\n",
						interface, offset, len);
			usleep(100000);
			continue;
		}

		if (rc < 0) {
			fprintf(stderr, "Communication error. (ftdi interface %c read rc=%d, %s)\n",
					interface, rc, ftdi_get_error_string(ftdi));
			exit(1);
		}

		retry_cnt = 0;
		offset += rc;
	}

	if (ftdi_verbose) {
		printf("ftdi-recv-%c>", interface);
		for (int i = 0; i < len; i++)
			printf(" %02x", buffer[i]);
		printf("\n");
	}
}

void my_ftdi_setup(struct ftdi_context *ftdi, enum ftdi_interface interface, const char *ifname)
{
	ftdi_init(ftdi);

	ftdi_set_interface(ftdi, interface);

	if (ftdi_usb_open(ftdi, 0x0403, 0x6010)) {
		fprintf(stderr, "Can't find IcoBoard USB baseboard (vedor_id 0x0403, device_id 0x6010, interface %s).\n", ifname);
		exit(1);
	}

	if (ftdi_usb_reset(ftdi)) {
		fprintf(stderr, "Failed to reset IcoBoard USB baseboard (interface %s).\n", ifname);
		exit(1);
	}

	if (ftdi_usb_purge_buffers(ftdi)) {
		fprintf(stderr, "Failed to purge buffers on IcoBoard USB baseboard (interface %s).\n", ifname);
		exit(1);
	}

	/* 1 is the fastest polling, it means 1 kHz polling */
	if (ftdi_set_latency_timer(ftdi, 1) < 0) {
		fprintf(stderr, "Failed to set latency timer (%s).\n", ftdi_get_error_string(ftdi));
		exit(1);
	}

	if (ftdi_set_bitmode(ftdi, 0xff, BITMODE_MPSSE) < 0) {
		fprintf(stderr, "Failed set BITMODE_MPSSE on IcoBoard USB baseboard (interface %s).\n", ifname);
		exit(1);
	}

	std::vector<uint8_t> cmd;

	// enable clock prescale divide by 5
	cmd.push_back(0x8b);

	// 6 MHz = 0
	// 1 MHz = 5
	// 100 kHz = 59
	// 10 kHz = 599
	int clkdiv = 0;

	cmd.push_back(0x86);
	cmd.push_back(clkdiv & 255);
	cmd.push_back(clkdiv >> 8);

	my_ftdi_send(ftdi, &cmd.front(), cmd.size());
}

void my_ftdi_wr(int pin)
{
	struct ftdi_context *ftdi = &ftdia;
	uint32_t new_dir = ftdistate_dir;
	uint32_t new_val = ftdistate_val;
	uint8_t opcode = 0x80;

	if (pin >= 16) {
		pin -= 16;
		ftdi = &ftdib;
		new_dir >>= 16;
		new_val >>= 16;
	}

	if (pin >= 8) {
		pin -= 8;
		opcode = 0x82;
		new_dir >>= 8;
		new_val >>= 8;
	}

	uint8_t cmd[3] = {opcode, uint8_t(new_val), uint8_t(new_dir)};
	my_ftdi_send(ftdi, cmd, 3);
}

void my_ftdi_pinmode(int pin, bool pinmode)
{
	if (pinmode)
		ftdistate_dir |= 1 << pin;
	else
		ftdistate_dir &= ~(1 << pin);

	my_ftdi_wr(pin);
}

void my_ftdi_pinwrite(int pin, bool pinvalue)
{
	if (pinvalue)
		ftdistate_val |= 1 << pin;
	else
		ftdistate_val &= ~(1 << pin);

	my_ftdi_wr(pin);
}

bool my_ftdi_pinread(int pin)
{
	struct ftdi_context *ftdi = &ftdia;
	uint8_t opcode = 0x81;

	if (pin >= 16) {
		pin -= 16;
		ftdi = &ftdib;
	}

	if (pin >= 8) {
		pin -= 8;
		opcode = 0x83;
	}

	uint8_t data;
	my_ftdi_send(ftdi, &opcode, 1);
	my_ftdi_recv(ftdi, &data, 1);

	return (data & (1 << pin)) != 0;
}

void wiringPiSetup()
{
	my_ftdi_setup(&ftdia, INTERFACE_A, "A");
	my_ftdi_setup(&ftdib, INTERFACE_B, "B");
	ftdistate_dir = 0;
	ftdistate_val = 0;
}

void pinMode(int pin, int dir)
{
	my_ftdi_pinmode(pin, dir != INPUT);
}

void digitalWrite(int pin, int val)
{
	my_ftdi_pinwrite(pin, val != LOW);
}

int digitalRead(int pin)
{
	return my_ftdi_pinread(pin) ? HIGH : LOW;
}

void digitalSync(int usec_delay)
{
	uint8_t request = 0x81;
	uint8_t response_a, response_b;

	my_ftdi_send(&ftdia, &request, 1);
	my_ftdi_recv(&ftdia, &response_a, 1);

	my_ftdi_send(&ftdib, &request, 1);
	my_ftdi_recv(&ftdib, &response_b, 1);

	usleep(usec_delay);
}

#define PININFO(pin) pininfo(#pin, pin);

void pininfo(const char *name, int pin)
{
	int dir = (ftdistate_dir >> pin) & 1;
	int val = (ftdistate_val >> pin) & 1;
	if (!dir) val = digitalRead(pin);

	fprintf(stderr, "%-20s %d %s\n", name, val, dir ? "OUT" : "IN");
}

#endif /* USBMODE */

// --------------------------------------------------------------------------------------------

#ifdef GPIOMODE

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

// Pinout for UP-board:
// https://up-community.org/wiki/Pinout

#  define RPI_ICE_CLK      4 // PIN  7
#  define RPI_ICE_CDONE   27 // PIN 13
#  define RPI_ICE_MOSI     5 // PIN 29
#  define RPI_ICE_MISO     6 // PIN 31
#  define LOAD_FROM_FLASH 13 // PIN 33
#  define RPI_ICE_CRESET  26 // PIN 37
#  define RPI_ICE_CS       8 // PIN 24
#  define RPI_ICE_SELECT  12 // PIN 32

#  define RASPI_D8  17 // PIN 11
#  define RASPI_D7  18 // PIN 12
#  define RASPI_D6  22 // PIN 15
#  define RASPI_D5  23 // PIN 16
#  define RASPI_D4  10 // PIN 19
#  define RASPI_D3   9 // PIN 21
#  define RASPI_D2   7 // PIN 26
#  define RASPI_D1  19 // PIN 35
#  define RASPI_D0  16 // PIN 36
#  define RASPI_DIR 20 // PIN 38
#  define RASPI_CLK 21 // PIN 40

#  define INPUT 0
#  define OUTPUT 1

#  define LOW 0
#  define HIGH 1

int gpio_direction[32];
int gpio_value[32];

int gpio_direction_fds[32];
int gpio_value_fds[32];

void wiringPiSetup()
{
	for (int i = 0; i < 32; i++) {
		gpio_direction[i] = -1;
		gpio_value[i] = -1;
		gpio_direction_fds[i] = -1;
		gpio_value_fds[i] = -1;
	}
}

void my_write(int fd, const void *buffer, int n)
{
	int rc = write(fd, buffer, n);

	if (rc != n) {
		fprintf(stderr, "Unexpected GPIO write error.\n");
		exit(1);
	}
}

void pinSetup(int pin)
{
	if (gpio_direction_fds[pin] < 0)
	{
		char buffer[4096];
		int f, n, rc;

		f = open("/sys/class/gpio/export", O_WRONLY);
		n = snprintf(buffer, 4096, "%d", pin);
		rc = write(f, buffer, n);
		if (rc != n && (rc != -1 || errno != EBUSY)) {
			fprintf(stderr, "Unexpected GPIO export error.\n");
			exit(1);
		}
		close(f);

		snprintf(buffer, 4096, "/sys/class/gpio/gpio%d/direction", pin);
		gpio_direction_fds[pin] = open(buffer, O_WRONLY);

		snprintf(buffer, 4096, "/sys/class/gpio/gpio%d/value", pin);
		gpio_value_fds[pin] = open(buffer, O_RDWR);

		my_write(gpio_direction_fds[pin], "in\n", 3);
		gpio_direction[pin] = 0;
		gpio_value[pin] = 0;
	}
}

void pinMode(int pin, int dir)
{
	pinSetup(pin);

	if (dir == INPUT)
	{
		if (gpio_direction[pin] == 0)
			return;

		my_write(gpio_direction_fds[pin], "in\n", 3);
		gpio_direction[pin] = 0;
	}
	else
	{
		if (gpio_direction[pin] == 1)
			return;

		if (gpio_value[pin])
			my_write(gpio_direction_fds[pin], "high\n", 5);
		else
			my_write(gpio_direction_fds[pin], "low\n", 4);

		gpio_direction[pin] = 1;
	}
}

void digitalWrite(int pin, int val)
{
	pinSetup(pin);
	gpio_value[pin] = (val != LOW);

	if (gpio_direction[pin] == 1) {
		if (gpio_value[pin])
			my_write(gpio_value_fds[pin], "1", 1);
		else
			my_write(gpio_value_fds[pin], "0", 1);
	}
}

int digitalRead(int pin)
{
	pinSetup(pin);

	if (gpio_direction[pin] == 0)
	{
		char buffer[4096];
		int n;

		lseek(gpio_value_fds[pin], 0, SEEK_SET);
		n = read(gpio_value_fds[pin], buffer, 4095);

		if (n > 0)
			gpio_value[pin] = buffer[0] != '0';
	}

	return gpio_value[pin] ? HIGH : LOW;;
}

void digitalSync(int usec_delay)
{
	usleep(usec_delay);
}

#endif /* GPIOMODE */

// --------------------------------------------------------------------------------------------

bool send_zero = false;
bool recv_zero = false;
char current_send_recv_mode = 0;
int current_recv_ep = -1;

int last_recv_v = -1;
int last_recv_rep = 0;

void fpga_reset()
{
	pinMode(RPI_ICE_CRESET,  OUTPUT);
	digitalWrite(RPI_ICE_CRESET, LOW);
	digitalSync(2000);
	digitalWrite(RPI_ICE_CRESET, HIGH);
	digitalSync(500000);
	if (digitalRead(RPI_ICE_CDONE) != HIGH) {
		fprintf(stderr, "Warning: cdone is low\n");
		got_error = true;
	}
}

int get_time_ms()
{
	static struct timespec spec_start;
	static bool spec_start_initialized = false;

	struct timespec spec_now;
	clock_gettime(CLOCK_REALTIME, &spec_now);
	if (!spec_start_initialized) {
		spec_start = spec_now;
		spec_start_initialized = true;
	}

	int s = spec_now.tv_sec - spec_start.tv_sec;
	int ns = spec_now.tv_nsec - spec_start.tv_nsec;

	return s*1000 + ns/1000000;
}

void prog_bitstream(bool reset_only = false)
{
	assert(enable_prog_port);

	pinMode(RPI_ICE_CLK,     OUTPUT);
	pinMode(RPI_ICE_MOSI,    OUTPUT);
	pinMode(LOAD_FROM_FLASH, OUTPUT);
	pinMode(RPI_ICE_CRESET,  OUTPUT);
	pinMode(RPI_ICE_CS,      OUTPUT);
	pinMode(RPI_ICE_SELECT,  OUTPUT);

	fprintf(stderr, "reset..\n");

	// enable reset
	digitalWrite(RPI_ICE_CRESET, LOW);

	// start clock high
	digitalWrite(RPI_ICE_CLK, HIGH);

	// select SRAM programming mode
	digitalWrite(LOAD_FROM_FLASH, LOW);
	digitalWrite(RPI_ICE_SELECT, LOW);
	digitalWrite(RPI_ICE_CS, LOW);
	digitalSync(100);

	// release reset
	digitalWrite(RPI_ICE_CRESET, HIGH);
	digitalSync(2000);

	fprintf(stderr, "cdone: %s\n", digitalRead(RPI_ICE_CDONE) == HIGH ? "high" : "low");

	if (reset_only)
		return;

	fprintf(stderr, "programming..\n");

	for (int i = 0; i < 8; i++) {
		digitalWrite(RPI_ICE_CLK, LOW);
		digitalWrite(RPI_ICE_CLK, HIGH);
	}

#ifndef USBMODE
	for (int k = 0;; k++)
	{
		int byte = getchar();
		if (byte < 0)
			break;
		for (int i = 7; i >= 0; i--) {
			digitalWrite(RPI_ICE_MOSI, ((byte >> i) & 1) ? HIGH : LOW);
			digitalWrite(RPI_ICE_CLK, LOW);
			digitalWrite(RPI_ICE_CLK, HIGH);
		}

		if (verbose && !(k % 1024) && k)
			printf("%3d kB written.\n", k / 1024);
	}

	for (int i = 0; i < 49; i++) {
		digitalWrite(RPI_ICE_CLK, LOW);
		digitalWrite(RPI_ICE_CLK, HIGH);
	}
#else
	std::vector<uint8_t> data;
	int sent_cnt = 0;

	while (1)
	{
		int byte = getchar();
		if (byte < 0)
			break;
		data.push_back(byte);
	}

	while (sent_cnt < int(data.size()))
	{
		uint8_t *buffer = &data[sent_cnt];
		int len = int(data.size()) - sent_cnt;

		if (len > 1024)
			len = 1024;

		uint8_t cmd[4] = {0x11, uint8_t(len-1), uint8_t((len-1) >> 8)};
		my_ftdi_send(&ftdib, cmd, 3);
		my_ftdi_send(&ftdib, buffer, len);
		sent_cnt += len;
	}

	// send 49 additional dummy bits
	uint8_t cmd[5] = {0x8f, 0x05, 0x00, 0x8e, 0x00};
	my_ftdi_send(&ftdib, cmd, 5);
#endif

	digitalSync(2000);
#if 0
	for (int i = 2; i <= 512; i+=2) {
		digitalSync(2000);
		if (((i-1) & i) == 0)
			fprintf(stderr, "cdone (after %3d ms): %s\n", i, digitalRead(RPI_ICE_CDONE) == HIGH ? "high" : "low");
	}
#else
	bool cdone_high = digitalRead(RPI_ICE_CDONE) == HIGH;
	fprintf(stderr, "cdone: %s\n", cdone_high ? "high" : "low");
	if (!cdone_high) got_error = true;
#endif
}

void spi_begin()
{
	digitalWrite(RPI_ICE_CS, LOW);
	// fprintf(stderr, "SPI_BEGIN\n");
}

void spi_end()
{
	digitalWrite(RPI_ICE_CS, HIGH);
	// fprintf(stderr, "SPI_END\n");
}

uint32_t spi_xfer(uint32_t data, int nbits = 8)
{
	assert(enable_prog_port);

#ifndef USBMODE
	uint32_t rdata = 0;

	for (int i = nbits-1; i >= 0; i--)
	{
		digitalWrite(RPI_ICE_MOSI, (data & (1 << i)) ? HIGH : LOW);

		digitalSync(1);
		if (digitalRead(RPI_ICE_MISO) == HIGH)
			rdata |= 1 << i;

		digitalWrite(RPI_ICE_CLK, HIGH);

		digitalWrite(RPI_ICE_CLK, LOW);
	}

	// fprintf(stderr, "SPI:%d %02x %02x\n", nbits, data, rdata);
	return rdata;
#else
	assert(nbits <= 8);

	uint8_t cmd[3] = {0x33, uint8_t(nbits-1), uint8_t(data)};
	uint8_t rdata;

	my_ftdi_send(&ftdib, cmd, 3);
	my_ftdi_recv(&ftdib, &rdata, 1);

	// fprintf(stderr, "SPI:%d %02x %02x\n", nbits, data, rdata);
	return rdata;
#endif
}

void flash_write_enable()
{
	spi_begin();
	spi_xfer(0x06);
	spi_end();
}

void flash_bulk_erase()
{
	spi_begin();
	spi_xfer(0xc7);
	spi_end();
}

void flash_erase_64kB(int addr)
{
	spi_begin();
	spi_xfer(0xd8);
	spi_xfer(addr >> 16);
	spi_xfer(addr >> 8);
	spi_xfer(addr);
	spi_end();
}

void flash_write(int addr, uint8_t *data, int n)
{
	spi_begin();
	spi_xfer(0x02);
	spi_xfer(addr >> 16);
	spi_xfer(addr >> 8);
	spi_xfer(addr);
#ifndef USBMODE
	while (n--)
		spi_xfer(*(data++));
#else
	assert(n <= 64*1024);
	uint8_t cmd[3] = {0x11, uint8_t(n-1), uint8_t((n-1) >> 8)};
	my_ftdi_send(&ftdib, cmd, 3);
	my_ftdi_send(&ftdib, data, n);
#endif
	spi_end();
}

void flash_read(int addr, uint8_t *data, int n)
{
	spi_begin();
	spi_xfer(0x03);
	spi_xfer(addr >> 16);
	spi_xfer(addr >> 8);
	spi_xfer(addr);
#ifndef USBMODE
	while (n--)
		*(data++) = spi_xfer(0);
#else
	assert(n <= 64*1024);
	uint8_t cmd[3] = {0x24, uint8_t(n-1), uint8_t((n-1) >> 8)};
	my_ftdi_send(&ftdib, cmd, 3);
	my_ftdi_recv(&ftdib, data, n);
#endif
	spi_end();
}

int flash_wait()
{
	int ms_start = get_time_ms();

	while (1)
	{
		spi_begin();
		spi_xfer(0x05);
		int status = spi_xfer(0);
		spi_end();

		if ((status & 0x01) == 0)
			break;

		digitalSync(1000);
	}

	return get_time_ms() - ms_start;
}

void prog_flasherase()
{
	assert(enable_prog_port);

	pinMode(RPI_ICE_CLK,     OUTPUT);
	pinMode(RPI_ICE_MOSI,    OUTPUT);
	pinMode(LOAD_FROM_FLASH, OUTPUT);
	pinMode(RPI_ICE_CS,      OUTPUT);
	pinMode(RPI_ICE_SELECT,  OUTPUT);

	// connect flash to Raspi
	digitalWrite(LOAD_FROM_FLASH, LOW);
	digitalWrite(RPI_ICE_SELECT, HIGH);
	digitalWrite(RPI_ICE_CS, HIGH);
	digitalWrite(RPI_ICE_CLK, LOW);
	digitalSync(100);

	// power_up
	spi_begin();
	spi_xfer(0xab);
	spi_end();

	flash_write_enable();
	flash_bulk_erase();

	// power_down
	spi_begin();
	spi_xfer(0xb9);
	spi_end();
}

void prog_flashmem(int pageoffset, bool erase_first_block)
{
	assert(enable_prog_port);

	pinMode(RPI_ICE_CLK,     OUTPUT);
	pinMode(RPI_ICE_MOSI,    OUTPUT);
	pinMode(LOAD_FROM_FLASH, OUTPUT);
	pinMode(RPI_ICE_CS,      OUTPUT);
	pinMode(RPI_ICE_SELECT,  OUTPUT);

	// connect flash to Raspi
	digitalWrite(LOAD_FROM_FLASH, LOW);
	digitalWrite(RPI_ICE_SELECT, HIGH);
	digitalWrite(RPI_ICE_CS, HIGH);
	digitalWrite(RPI_ICE_CLK, LOW);
	digitalSync(100);

	// power_up
	spi_begin();
	spi_xfer(0xab);
	spi_end();

	// read flash id
	spi_begin();
	spi_xfer(0x9f);
	fprintf(stderr, "flash id:");
	for (int i = 0; i < 20; i++)
		fprintf(stderr, " %02x", spi_xfer(0x00));
	fprintf(stderr, "\n");
	spi_end();

	// load prog data into buffer
	std::vector<uint8_t> prog_data;
	if (erase_first_block)
	{
		prog_data.push_back(0);
	}
	else
	{
		while (1) {
			int byte = getchar();
			if (byte < 0)
				break;
			prog_data.push_back(byte);
		}

		fprintf(stderr, "writing %.2fkB..", double(prog_data.size()) / 1024);
	}

	int ms_timer = 0;
	for (int addr = 0; addr < int(prog_data.size()); addr += 256)
	{
		if (addr % (64*1024) == 0)
		{
			if (erase_first_block) {
				fprintf(stderr, "erasing 64kB sector @%06x..", addr);
			} else {
				fprintf(stderr, "\n%3d%% @%06x ", 100*addr/int(prog_data.size()), addr);
				fprintf(stderr, "erasing 64kB sector..");
			}

			flash_write_enable();
			flash_erase_64kB(addr + pageoffset * 0x10000);
			ms_timer += flash_wait();

			if (erase_first_block)
				break;
		}

		if (addr % (32*256) == 0) {
			fprintf(stderr, "\n%3d%% @%06x writing: ", 100*addr/int(prog_data.size()), addr);
		}

		int n = std::min(256, int(prog_data.size()) - addr);
		uint8_t buffer[256];

		for (int retry_count = 0; retry_count < 100; retry_count++)
		{
			flash_write_enable();
			flash_write(addr + pageoffset * 0x10000, &prog_data[addr], n);
			ms_timer += flash_wait();

			flash_read(addr + pageoffset * 0x10000, buffer, n);

			if (!memcmp(buffer, &prog_data[addr], n)) {
				fprintf(stderr, "o");
				goto written_ok;
			}

			fprintf(stderr, "X");
		}

		// restart erasing and writing this 64kB sector
		addr -= addr % (64*1024);
		addr -= 256;

	written_ok:;
	}

	fprintf(stderr, "\n%stotal wait time: %d ms\n", erase_first_block ? "" : "100% ", ms_timer);

	// power_down
	spi_begin();
	spi_xfer(0xb9);
	spi_end();
}

void read_flashmem(int n)
{
	assert(enable_prog_port);

	pinMode(RPI_ICE_CLK,     OUTPUT);
	pinMode(RPI_ICE_MOSI,    OUTPUT);
	pinMode(LOAD_FROM_FLASH, OUTPUT);
	pinMode(RPI_ICE_CS,      OUTPUT);
	pinMode(RPI_ICE_SELECT,  OUTPUT);

	// connect flash to Raspi
	digitalWrite(LOAD_FROM_FLASH, LOW);
	digitalWrite(RPI_ICE_SELECT, HIGH);
	digitalWrite(RPI_ICE_CS, HIGH);
	digitalWrite(RPI_ICE_CLK, LOW);
	digitalSync(100);

	// power_up
	spi_begin();
	spi_xfer(0xab);
	spi_end();

	// read flash id
	spi_begin();
	spi_xfer(0x9f);
	fprintf(stderr, "flash id:");
	for (int i = 0; i < 20; i++)
		fprintf(stderr, " %02x", spi_xfer(0x00));
	fprintf(stderr, "\n");
	spi_end();

	if (n > 0)
		fprintf(stderr, "reading %.2fkB..\n", double(n) / 1024);

	for (int addr = 0; addr < n; addr += 256) {
		uint8_t buffer[256];
		flash_read(addr, buffer, std::min(256, n - addr));
		fwrite(buffer, std::min(256, n - addr), 1, stdout);
	}

	// power_down
	spi_begin();
	spi_xfer(0xb9);
	spi_end();
}

void epsilon_sleep()
{
#ifndef USBMODE
	for (int i = 0; i < 1000; i++)
		asm volatile ("");
#endif
}

void send_word(int v)
{
	assert(enable_data_port);
#ifndef USBMODE
	if (current_send_recv_mode != 's')
	{
		digitalWrite(RASPI_DIR, HIGH);
		epsilon_sleep();

		pinMode(RASPI_D8, OUTPUT);
		pinMode(RASPI_D7, OUTPUT);
		pinMode(RASPI_D6, OUTPUT);
		pinMode(RASPI_D5, OUTPUT);
		pinMode(RASPI_D4, OUTPUT);
		pinMode(RASPI_D3, OUTPUT);
		pinMode(RASPI_D2, OUTPUT);
		pinMode(RASPI_D1, OUTPUT);
		pinMode(RASPI_D0, OUTPUT);

		current_send_recv_mode = 's';
	}

	if (verbose) {
		last_recv_v = -1;
		last_recv_rep = 0;
		fprintf(stderr, "<%03x>", v);
		fflush(stderr);
	}

	digitalWrite(RASPI_D8, (v & 0x100) ? HIGH : LOW);
	digitalWrite(RASPI_D7, (v & 0x080) ? HIGH : LOW);
	digitalWrite(RASPI_D6, (v & 0x040) ? HIGH : LOW);
	digitalWrite(RASPI_D5, (v & 0x020) ? HIGH : LOW);
	digitalWrite(RASPI_D4, (v & 0x010) ? HIGH : LOW);
	digitalWrite(RASPI_D3, (v & 0x008) ? HIGH : LOW);
	digitalWrite(RASPI_D2, (v & 0x004) ? HIGH : LOW);
	digitalWrite(RASPI_D1, (v & 0x002) ? HIGH : LOW);
	digitalWrite(RASPI_D0, (v & 0x001) ? HIGH : LOW);

	epsilon_sleep();
	digitalWrite(RASPI_CLK, HIGH);
	epsilon_sleep();
	digitalWrite(RASPI_CLK, LOW);
	epsilon_sleep();
#else
	if (current_send_recv_mode != 's')
	{
		ftdistate_val |= 1 << RASPI_DIR;

		ftdistate_dir |= 1 << RASPI_D8;
		ftdistate_dir |= 1 << RASPI_D7;
		ftdistate_dir |= 1 << RASPI_D6;
		ftdistate_dir |= 1 << RASPI_D5;
		ftdistate_dir |= 1 << RASPI_D4;
		ftdistate_dir |= 1 << RASPI_D3;
		ftdistate_dir |= 1 << RASPI_D2;
		ftdistate_dir |= 1 << RASPI_D1;
		ftdistate_dir |= 1 << RASPI_D0;

		std::vector<uint8_t> cmd;

		cmd.push_back(0x80);
		cmd.push_back(ftdistate_val);
		cmd.push_back(ftdistate_dir);

		cmd.push_back(0x82);
		cmd.push_back(ftdistate_val >> 8);
		cmd.push_back(ftdistate_dir >> 8);

		my_ftdi_send(&ftdia, &cmd.front(), cmd.size());
		current_send_recv_mode = 's';
	}

	if (verbose) {
		last_recv_v = -1;
		last_recv_rep = 0;
		fprintf(stderr, "<%03x>", v);
		fflush(stderr);
	}

	std::vector<uint8_t> cmd;

	ftdistate_val &= ~(1 << RASPI_D8);
	ftdistate_val &= ~(1 << RASPI_D7);
	ftdistate_val &= ~(1 << RASPI_D6);
	ftdistate_val &= ~(1 << RASPI_D5);
	ftdistate_val &= ~(1 << RASPI_D4);
	ftdistate_val &= ~(1 << RASPI_D3);
	ftdistate_val &= ~(1 << RASPI_D2);
	ftdistate_val &= ~(1 << RASPI_D1);
	ftdistate_val &= ~(1 << RASPI_D0);

	if ((v & 0x100) != 0) ftdistate_val |= 1 << RASPI_D8;
	if ((v & 0x080) != 0) ftdistate_val |= 1 << RASPI_D7;
	if ((v & 0x040) != 0) ftdistate_val |= 1 << RASPI_D6;
	if ((v & 0x020) != 0) ftdistate_val |= 1 << RASPI_D5;
	if ((v & 0x010) != 0) ftdistate_val |= 1 << RASPI_D4;
	if ((v & 0x008) != 0) ftdistate_val |= 1 << RASPI_D3;
	if ((v & 0x004) != 0) ftdistate_val |= 1 << RASPI_D2;
	if ((v & 0x002) != 0) ftdistate_val |= 1 << RASPI_D1;
	if ((v & 0x001) != 0) ftdistate_val |= 1 << RASPI_D0;

	cmd.push_back(0x80);
	cmd.push_back(ftdistate_val);
	cmd.push_back(ftdistate_dir);

	cmd.push_back(0x82);
	cmd.push_back(ftdistate_val >> 8);
	cmd.push_back(ftdistate_dir >> 8);

	ftdistate_val |= 1 << RASPI_CLK;

	cmd.push_back(0x80);
	cmd.push_back(ftdistate_val);
	cmd.push_back(ftdistate_dir);

	cmd.push_back(0x82);
	cmd.push_back(ftdistate_val >> 8);
	cmd.push_back(ftdistate_dir >> 8);

	ftdistate_val &= ~(1 << RASPI_CLK);

	cmd.push_back(0x80);
	cmd.push_back(ftdistate_val);
	cmd.push_back(ftdistate_dir);

	cmd.push_back(0x82);
	cmd.push_back(ftdistate_val >> 8);
	cmd.push_back(ftdistate_dir >> 8);

	my_ftdi_send(&ftdia, &cmd.front(), cmd.size());
#endif
}

int recv_word(int timeout = 0)
{
	assert(enable_data_port);
#ifndef USBMODE
	if (current_send_recv_mode != 'r')
	{
		pinMode(RASPI_D8, INPUT);
		pinMode(RASPI_D7, INPUT);
		pinMode(RASPI_D6, INPUT);
		pinMode(RASPI_D5, INPUT);
		pinMode(RASPI_D4, INPUT);
		pinMode(RASPI_D3, INPUT);
		pinMode(RASPI_D2, INPUT);
		pinMode(RASPI_D1, INPUT);
		pinMode(RASPI_D0, INPUT);

		digitalWrite(RASPI_DIR, LOW);
		epsilon_sleep();

		current_send_recv_mode = 'r';
	}

	int v = 0;

	if (digitalRead(RASPI_D8) == HIGH) v |= 0x100;
	if (digitalRead(RASPI_D7) == HIGH) v |= 0x080;
	if (digitalRead(RASPI_D6) == HIGH) v |= 0x040;
	if (digitalRead(RASPI_D5) == HIGH) v |= 0x020;
	if (digitalRead(RASPI_D4) == HIGH) v |= 0x010;
	if (digitalRead(RASPI_D3) == HIGH) v |= 0x008;
	if (digitalRead(RASPI_D2) == HIGH) v |= 0x004;
	if (digitalRead(RASPI_D1) == HIGH) v |= 0x002;
	if (digitalRead(RASPI_D0) == HIGH) v |= 0x001;

	epsilon_sleep();
	digitalWrite(RASPI_CLK, HIGH);
	epsilon_sleep();
	digitalWrite(RASPI_CLK, LOW);
	epsilon_sleep();
#else
	if (current_send_recv_mode != 'r')
	{
		ftdistate_val &= ~(1 << RASPI_DIR);

		ftdistate_dir &= ~(1 << RASPI_D8);
		ftdistate_dir &= ~(1 << RASPI_D7);
		ftdistate_dir &= ~(1 << RASPI_D6);
		ftdistate_dir &= ~(1 << RASPI_D5);
		ftdistate_dir &= ~(1 << RASPI_D4);
		ftdistate_dir &= ~(1 << RASPI_D3);
		ftdistate_dir &= ~(1 << RASPI_D2);
		ftdistate_dir &= ~(1 << RASPI_D1);
		ftdistate_dir &= ~(1 << RASPI_D0);

		std::vector<uint8_t> cmd;

		cmd.push_back(0x80);
		cmd.push_back(ftdistate_val);
		cmd.push_back(ftdistate_dir);

		cmd.push_back(0x82);
		cmd.push_back(ftdistate_val >> 8);
		cmd.push_back(ftdistate_dir >> 8);

		my_ftdi_send(&ftdia, &cmd.front(), cmd.size());
		current_send_recv_mode = 'r';
	}

	std::vector<uint8_t> cmd;
	uint8_t cmd_response[2];

	cmd.push_back(0x81);
	cmd.push_back(0x83);

	ftdistate_val |= 1 << RASPI_CLK;

	cmd.push_back(0x80);
	cmd.push_back(ftdistate_val);
	cmd.push_back(ftdistate_dir);

	cmd.push_back(0x82);
	cmd.push_back(ftdistate_val >> 8);
	cmd.push_back(ftdistate_dir >> 8);

	ftdistate_val &= ~(1 << RASPI_CLK);

	cmd.push_back(0x80);
	cmd.push_back(ftdistate_val);
	cmd.push_back(ftdistate_dir);

	cmd.push_back(0x82);
	cmd.push_back(ftdistate_val >> 8);
	cmd.push_back(ftdistate_dir >> 8);

	my_ftdi_send(&ftdia, &cmd.front(), cmd.size());
	my_ftdi_recv(&ftdia, cmd_response, 2);

	int v = 0;
	uint16_t pindata = (cmd_response[1] << 8) | cmd_response[0];

	if ((pindata & (1 << RASPI_D8)) != 0 ) v |= 0x100;
	if ((pindata & (1 << RASPI_D7)) != 0 ) v |= 0x080;
	if ((pindata & (1 << RASPI_D6)) != 0 ) v |= 0x040;
	if ((pindata & (1 << RASPI_D5)) != 0 ) v |= 0x020;
	if ((pindata & (1 << RASPI_D4)) != 0 ) v |= 0x010;
	if ((pindata & (1 << RASPI_D3)) != 0 ) v |= 0x008;
	if ((pindata & (1 << RASPI_D2)) != 0 ) v |= 0x004;
	if ((pindata & (1 << RASPI_D1)) != 0 ) v |= 0x002;
	if ((pindata & (1 << RASPI_D0)) != 0 ) v |= 0x001;
#endif

	if (verbose)
	{
		if (v != last_recv_v) {
			last_recv_v = v;
			last_recv_rep = 0;
		} else {
			last_recv_rep++;
		}

		if ((v == 0x1fe || v == 0x1ff) && last_recv_rep > 0) {
			if (last_recv_rep == 1) {
				fprintf(stderr, "[%03x..]", v);
				if (v == 0x1ff)
					fprintf(stderr, "\r\n");
				fflush(stderr);
			}
		} else {
			fprintf(stderr, "[%03x]", v);
			if (v == 0x1ff)
				fprintf(stderr, "\r\n");
			fflush(stderr);
		}
	}

	if (v >= 0x100)
		current_recv_ep = v & 0xff;

	if (timeout && (v == 0x1ff || v == 0x1fe)) {
		if (timeout == 1) {
			fprintf(stderr, "Timeout!\n");
			exit(1);
		}
		return recv_word(timeout - 1);
	}

	return v;
}

void link_sync(int trignum = -1)
{
	while (recv_word() != 0x1ff) { }

	send_word(0x1ff);
	send_word(0x0ff);

	if (trignum >= 0)
		send_word(trignum);

	while (recv_word() == 0x1fe) { }
}

void test_link()
{
	link_sync();
	send_word(0x100);

	srandom(time(NULL));

	for (int k = 0; k < 1000; k++)
	{
		int data_out[20], data_in[20], data_exp[20];

		fprintf(stderr, "Round %d:\n", k);

		for (int i = 0; i < 20; i++) {
			data_out[i] = random() & 255;
			data_exp[i] = (((data_out[i] << 5) + data_out[i]) ^ 7) & 255;
			send_word(data_out[i]);
		}

		for (int i = 0; i < 20; i++)
			fprintf(stderr, "%5d", data_out[i]);
		fprintf(stderr, "\n");

		for (int i = 0; i < 20; i++)
			do {
				data_in[i] = recv_word(64);
			} while (data_in[i] >= 0x100 || current_recv_ep != 0);

		for (int i = 0; i < 20; i++)
			fprintf(stderr, "%5d", data_in[i]);
		fprintf(stderr, "\n");

		for (int i = 0; i < 20; i++)
			if (data_in[i] == data_exp[i])
				fprintf(stderr, "%5s", "ok");
			else
				fprintf(stderr, " E%3d", data_exp[i]);
		fprintf(stderr, "\n");

		for (int i = 0; i < 20; i++)
			if (data_in[i] != data_exp[i]) {
				fprintf(stderr, "Test(s) failed!\n");
				exit(1);
			}
	}

	fprintf(stderr, "All tests passed.\n");
}

void test_bw()
{
	fprintf(stderr, "Sending and receiving 1 MB of test data ..\n");

	link_sync();
	send_word(0x100);

	for (int k = 0; k < 1024*1024/64; k++)
	{
		for (int i = 0; i < 64; i++)
			send_word(k ^ i);

		while (recv_word() != 0x1ff) { }
	}
}

void write_endpoint(int epnum, int trignum)
{
	link_sync(trignum);
	send_word(0x100 + epnum);

	for (int i = 0;; i++)
	{
		int byte = getchar();
		if (byte < 0 || 255 < byte)
			break;
		send_word(byte);

		if (i % 128 == 127)
			while (recv_word() != 0x1ff) { }
	}

	if (send_zero)
		send_word(0);

	link_sync();
}

void read_endpoint(int epnum, int trignum)
{
	link_sync(trignum);

	bool pending_fflush = false;

	for (int timeout = 0; timeout < 1000 || recv_zero; timeout++) {
		int byte = recv_word();
		if (current_recv_ep == epnum && byte < 0x100) {
			if (recv_zero && byte == 0)
				break;
			putchar(byte);
			pending_fflush = true;
			timeout = 0;
		} else if (pending_fflush) {
			pending_fflush = false;
			fflush(stdout);
		}
	}

	link_sync();
}

void console_endpoint(int epnum, int trignum)
{
	struct termios oldkey_stdin, oldkey_stdout, newkey;
	int is_tty = isatty(STDIN_FILENO);

	link_sync(trignum);
	send_word(0x100 + epnum);

	if (is_tty) {
		tcgetattr(STDIN_FILENO, &oldkey_stdin);
		tcgetattr(STDOUT_FILENO, &oldkey_stdout);
		memset(&newkey, 0, sizeof(newkey));
		newkey.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
		newkey.c_iflag = IGNPAR;
		newkey.c_oflag = ONLCR;
		newkey.c_lflag = 0;
		newkey.c_cc[VMIN]=1;
		newkey.c_cc[VTIME]=0;
		tcflush(STDIN_FILENO, TCIFLUSH);
		tcflush(STDOUT_FILENO, TCIFLUSH);
		tcsetattr(STDIN_FILENO, TCSANOW, &newkey);
		tcsetattr(STDOUT_FILENO, TCSANOW, &newkey);
	}

	bool running = true;
	int wrcount = 0;

	while (running)
	{
		struct timeval timeout = { 0, 10000 };
		int max_fd = STDIN_FILENO+1;
		fd_set fds;

		FD_ZERO(&fds);
		FD_SET(STDIN_FILENO, &fds);

		int ret = select(max_fd, &fds, NULL, NULL, &timeout);

		if (ret < 0)
			break;

		if (ret > 0) {
			char ch = 0;
			ret = read(STDIN_FILENO, &ch, 1);
			if (ret == 0 || ch == 3) {
				running = false;
				if (send_zero)
					send_word(ch);
				digitalSync(10000);
			} else {
				wrcount++;
				send_word(ch);
				if (wrcount < 200)
					continue;
			}
		}

		int stop_cnt = 0;
		while (1) {
			int v = recv_word();
			if ((v == 0x1ff) || (v == 0x1fe && wrcount < 100)) {
				if (v == 0x1ff)
					wrcount = 0;
				if (!running && stop_cnt < 10) {
					stop_cnt++;
					digitalSync(10000);
					continue;
				}
				if (!running && recv_zero)
					continue;
				break;
			}
			if (current_recv_ep == epnum && v < 0x100) {
				char ch = v;
				if (recv_zero && ch == 0)
					break;
				if (ch == '\n') {
					int rc = write(STDOUT_FILENO, "\r", 1);
					if (rc != 1) abort();
				}
				int rc = write(STDOUT_FILENO, &ch, 1);
				if (rc != 1) abort();
				stop_cnt = 0;
			}
		}
	}

	if (is_tty) {
		tcsetattr(STDIN_FILENO, TCSANOW, &oldkey_stdin);
		tcsetattr(STDOUT_FILENO, TCSANOW, &oldkey_stdout);
	}

	link_sync();
}

void read_dbgvcd(int nbits)
{
	link_sync(1);

	fprintf(stderr, "Waiting for trigger: ");
	printf("$var event 1 ! clock $end\n");
	for (int i = 0; i < nbits; i++)
		printf("$var wire 1 n%d debug_%d $end\n", i, i);
	printf("$enddefinitions $end\n");

	int nbytes = (nbits+7) / 8;
	int clock_cnt = 0;
	int byte_cnt = 0;
	bool waiting = true;

	for (int timeout = 0; timeout < 1000; timeout++)
	{
		int byte = recv_word();

		if (waiting)
			timeout = 0;

		if (current_recv_ep != 1 || byte >= 0x100)
			continue;

		if (waiting) {
			fprintf(stderr, "Triggered.\n");
			fprintf(stderr, "Downloading: ");
			waiting = false;
		}

		if (byte_cnt == 0)
			printf("#%d\n1!\n", clock_cnt);

		for (int bit = 0;  8*byte_cnt + bit < nbits && bit < 8; bit++)
			printf("b%d n%d\n", (byte >> bit) & 1, 8*byte_cnt + bit);

		if (++byte_cnt == nbytes) {
			fprintf(stderr, ".");
			byte_cnt = 0;
			clock_cnt++;
		}

		timeout = 0;
	}

	fprintf(stderr, "\nReceived %d cycles of debug data.\n", clock_cnt);
	link_sync();
}

void reset_inout()
{
	if (enable_prog_port)
	{
		pinMode(RPI_ICE_CLK,     4);
		pinMode(RPI_ICE_CDONE,   INPUT);
		pinMode(RPI_ICE_MOSI,    4);
		pinMode(RPI_ICE_MISO,    4);
		pinMode(LOAD_FROM_FLASH, INPUT);
		pinMode(RPI_ICE_CRESET,  INPUT);
		pinMode(RPI_ICE_CS,      OUTPUT);
		pinMode(RPI_ICE_SELECT,  OUTPUT);
	}

	if (enable_data_port)
	{
		pinMode(RASPI_D8, INPUT);
		pinMode(RASPI_D7, INPUT);
		pinMode(RASPI_D6, INPUT);
		pinMode(RASPI_D5, INPUT);
		pinMode(RASPI_D4, INPUT);
		pinMode(RASPI_D3, INPUT);
		pinMode(RASPI_D2, INPUT);
		pinMode(RASPI_D1, INPUT);
		pinMode(RASPI_D0, INPUT);

		pinMode(RASPI_DIR, OUTPUT);
		pinMode(RASPI_CLK, OUTPUT);

		digitalWrite(RASPI_DIR, LOW);
		digitalWrite(RASPI_CLK, LOW);

		current_send_recv_mode = 0;
	}
}

void help(const char *progname)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "Resetting FPGA:\n");
	fprintf(stderr, "    %s -R\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Resetting FPGA (reload from flash):\n");
	fprintf(stderr, "    %s -b\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Erase first flash block:\n");
	fprintf(stderr, "    %s -e\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Bulk erase entire flash:\n");
	fprintf(stderr, "    %s -E\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Programming FPGA bit stream:\n");
	fprintf(stderr, "    %s -p < data.bin\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Programming serial flash:\n");
	fprintf(stderr, "    %s -f < data.bin\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Reading serial flash (first N bytes):\n");
	fprintf(stderr, "    %s -F N > data.bin\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Testing bit-parallel link (using ep0):\n");
	fprintf(stderr, "    %s -T\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Testing link bandwidth (using ep0):\n");
	fprintf(stderr, "    %s -B\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Writing a file to ep N:\n");
	fprintf(stderr, "    %s -w N < data.bin\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Reading a file from ep N:\n");
	fprintf(stderr, "    %s -r N > data.bin\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Console at ep N:\n");
	fprintf(stderr, "    %s -c N\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Dumping a VCD file (from ep1, using trig1)\n");
	fprintf(stderr, "  with a debug core with N bits width:\n");
	fprintf(stderr, "    %s -V N > dbg_trace.vcd\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Additional options:\n");
	fprintf(stderr, "    -v      verbose output\n");
	fprintf(stderr, "    -O N    offset (in 64 kB pages) for -f and -e\n");
	fprintf(stderr, "    -z      send a terminating zero byte with -w/-c\n");
	fprintf(stderr, "    -Z      wait for terminating zero byte in -r/-c\n");
	fprintf(stderr, "    -t N    send trigger N before -w/-r/-c\n");
	fprintf(stderr, "\n");
	exit(1);
}

int main(int argc, char **argv)
{
	int opt, n = -1, t = -1;
	int pageoffset = 0;
	char mode = 0;

	while ((opt = getopt(argc, argv, "RbEpfeF:TBw:r:c:vzZt:O:V:")) != -1)
	{
		switch (opt)
		{
		case 'w':
		case 'r':
		case 'c':
		case 'V':
		case 'F':
			n = atoi(optarg);
			// fall through

		case 'E':
		case 'R':
		case 'b':
		case 'p':
		case 'f':
		case 'e':
		case 'T':
		case 'B':
			if (mode)
				help(argv[0]);
			mode = opt;
			break;

		case 'v':
			if (verbose)
				ftdi_verbose = true;
			verbose = true;
			break;

		case 'z':
			send_zero = true;
			break;

		case 'Z':
			recv_zero = true;
			break;

		case 't':
			t = atoi(optarg);
			break;

		case 'O':
			pageoffset = atoi(optarg);
			break;

		default:
			help(argv[0]);
		}
	}

	if (optind != argc || !mode)
		help(argv[0]);

	if (mode == 'R') {
		enable_prog_port = true;
		wiringPiSetup();
		reset_inout();
		prog_bitstream(true);
		reset_inout();
	}

	if (mode == 'b') {
		enable_prog_port = true;
		wiringPiSetup();
		reset_inout();
		fpga_reset();
		reset_inout();
	}

	if (mode == 'E') {
		enable_prog_port = true;
		wiringPiSetup();
		reset_inout();
		prog_flasherase();
		reset_inout();
	}

	if (mode == 'p') {
		enable_prog_port = true;
		wiringPiSetup();
		reset_inout();
		prog_bitstream();
		//reset_inout();
	}

	if (mode == 'f') {
		enable_prog_port = true;
		wiringPiSetup();
		reset_inout();
		prog_flashmem(pageoffset, false);
		reset_inout();
	}

	if (mode == 'e') {
		enable_prog_port = true;
		wiringPiSetup();
		reset_inout();
		prog_flashmem(pageoffset, true);
		reset_inout();
	}

	if (mode == 'F') {
		enable_prog_port = true;
		wiringPiSetup();
		reset_inout();
		read_flashmem(n);
		reset_inout();
	}

	if (mode == 'T') {
		enable_data_port = true;
		wiringPiSetup();
		reset_inout();
		test_link();
		reset_inout();
	}

	if (mode == 'B') {
		enable_data_port = true;
		wiringPiSetup();
		reset_inout();
		test_bw();
		reset_inout();
	}

	if (mode == 'w') {
		enable_data_port = true;
		wiringPiSetup();
		reset_inout();
		write_endpoint(n, t);
		reset_inout();
	}

	if (mode == 'r') {
		enable_data_port = true;
		wiringPiSetup();
		reset_inout();
		read_endpoint(n, t);
		reset_inout();
	}

	if (mode == 'c') {
		enable_data_port = true;
		wiringPiSetup();
		reset_inout();
		console_endpoint(n, t);
		reset_inout();
	}

	if (mode == 'V') {
		enable_data_port = true;
		wiringPiSetup();
		reset_inout();
		read_dbgvcd(n);
		reset_inout();
	}

	if (verbose)
		fprintf(stderr, "\n");

#if 0
#ifdef USBMODE
	PININFO(RPI_ICE_CLK);
	PININFO(RPI_ICE_CDONE);
	PININFO(RPI_ICE_MOSI);
	PININFO(RPI_ICE_MISO);
	PININFO(LOAD_FROM_FLASH);

	PININFO(RPI_ICE_CRESET);
	PININFO(RPI_ICE_CS);
	PININFO(RPI_ICE_SELECT);

	PININFO(RASPI_D8);
	PININFO(RASPI_D7);
	PININFO(RASPI_D6);
	PININFO(RASPI_D5);
	PININFO(RASPI_D4);
	PININFO(RASPI_D3);
	PININFO(RASPI_D2);
	PININFO(RASPI_D1);
	PININFO(RASPI_D0);

	PININFO(RASPI_DIR);
	PININFO(RASPI_CLK);
#endif
#endif

	return got_error ? 1 : 0;
}

