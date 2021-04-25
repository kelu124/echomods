'''
Wrapper over FTDI API
'''

from pyftdi.ftdi import Ftdi
from pyftdi.spi import SpiController
from pyftdi.gpio import GpioAsyncController


class FtdiDevice:
    """FTDI FT2232H SPI master to access FPGA Control/Status Registers (CSR)
    plus some GPIO control.

    SPI parameters:
      - FTDI channel B:
        * BDBUS0 - SCLK
        * BDBUS1 - MOSI
        * BDBUS2 - MISO
        * BDBUS3 - CSn
      - slave;
      - mode 0 only;
      - most significant bit transmitted first;
      - byte order from high to low;
      - SCK frequency must at least 8 lower than system frequency.

    There are 2 types of SPI transactions:
      - incremental burst -- address increments internally after every data (array)
      - fixed burst -- one adreess, multiple data (FIFO)
    Transaction is done with 8-bit address and 16 bit data words.
    Transaction format:
      - control word (3 bytes):
          * bit 23 -- write (1) or read (0)
          * bit 22 -- burst incremental (1) or fixed (0)
          * bit 21 .. 8 -- 14 bit length (0 - 1 data word, 1 - 2 data words, etc)
          * bits 7 .. 0 -- 8 bit address
      - data word (2 bytes) 1 .. N:
          * bits 15 .. 0 -- data to be written or readen

    GPIO parameters:
      - ADBUS7 - output - active low reset for FPGA configuration (ICE_RESET)
      - BDBUS7 - output - active high reset for FPGA logic (ICE_RESET_FT)
    """

    GPIO_RESET_LOGIC_POS = 7
    GPIO_RESET_CONFIG_POS = 7

    def __init__(self, ftdi_url, spi_freq=1E6):
        """Configure the FTDI interface.

        Keyword arguments:
         ftdi_url -- device url, which can be obtained by Ftdi.show_devices()
         freq -- SPI frequency up to 8E6 (for FPGA running on 64 MHz)
        """
        # Configure SPI master
        self._spi_ctrl = SpiController()
        self._spi_ctrl.configure(ftdi_url + '2') # second port - channel B
        self._spi_port = self._spi_ctrl.get_port(cs=0, freq=spi_freq, mode=0)
        # Configure FPGA logic reset (ICE_RESET_FT)
        self._spi_gpio = self._spi_ctrl.get_gpio()
        self._spi_gpio.set_direction(1 << self.GPIO_RESET_LOGIC_POS, 1 << self.GPIO_RESET_LOGIC_POS)
        self._spi_gpio.write(0)
        # Configure FPGA configuration reset (ICE_RESET)
        self._gpio_ctrl = GpioAsyncController()
        self._gpio_ctrl.configure(ftdi_url + '1', # first port - channel A
                                  direction=(1 << self.GPIO_RESET_CONFIG_POS),
                                  frequency=1e6,
                                  initial=(1 << self.GPIO_RESET_CONFIG_POS))
        self._gpio_ctrl.write(1 << self.GPIO_RESET_CONFIG_POS)

    def _int_to_bytes(self, i, length=2):
        """Convert integer to bytes"""
        return int.to_bytes(i, length=length, byteorder='big', signed=False)

    def _words_to_bytes(self, words_list):
        """Convert list with 16 bit words to bytes"""
        bytes_str_list = [self._int_to_bytes(w, length=2) for w in words_list]
        return b''.join(bytes_str_list)  # concatenate all strings

    def _bytes_to_words(self, bytes_str):
        """Convert bytes string to list with 16 bit words"""
        return [int.from_bytes(bytes_str[b*2:b*2+2], byteorder='big', signed=False) for b in range(len(bytes_str)//2)]

    def _prepare_ctrl_word(self, addr, len, burst, wr):
        """Prepare control word for exchange.

           Keyword arguments:
             addr -- 8 bit address
             len -- number of 16 bit data words to write/read (2^14 max)
             burst -- 'fixed' address the same for every data, 'incr' - address + 1 for every next data word
             wr -- 1 for write operation, 0 - for read
        """
        ctrl_word = 0
        ctrl_word |= (wr << 23)
        ctrl_word |= ((burst == 'incr') << 22)
        ctrl_word |= (((len - 1) & 0x3FFF) << 8)
        ctrl_word |= ((addr & 0xFF) << 0)
        return ctrl_word

    def spi_read(self, addr, len=1, burst='fixed'):
        """Read data from address via SPI.

           Keyword arguments:
             addr -- 8 bit address
             len -- number of 16 bit data words to write/read (2^14 max)
             burst -- 'fixed' address the same for every data, 'incr' - address + 1 for every next data word
           Return:
             list of size 'len' with 16 bit data words
        """
        ctrl_word = self._prepare_ctrl_word(addr, len, burst, wr=0)
        rbytes = self._spi_port.exchange(self._int_to_bytes(ctrl_word, 3), len * 2)
        return self._bytes_to_words(rbytes)

    def spi_write(self, addr, data, burst='fixed'):
        """Write data to address via SPI.

           Keyword arguments:
             addr -- 8 bit address
             data -- list with 16 bit data words to write (list length 2^14 max)
             burst -- 'fixed' address the same for every data, 'incr' - address + 1 for every next data word
         """
        ctrl_word = self._prepare_ctrl_word(addr, len(data), burst, wr=1)
        wbytes = self._int_to_bytes(ctrl_word, 3) + self._words_to_bytes(data)
        self._spi_port.exchange(wbytes)

    def reset_logic_on(self):
        """Activate reset pin ICE_RESET_FT"""
        self._spi_gpio.write((1 << self.GPIO_RESET_LOGIC_POS) | self._spi_gpio.read())

    def reset_logic_off(self):
        """Deactivate reset pin ICE_RESET_FT"""
        self._spi_gpio.write(~(1 << self.GPIO_RESET_LOGIC_POS) & self._spi_gpio.read())

    def reset_config_on(self):
        """Activate reset pin ICE_RESET"""
        self._gpio_ctrl.write(~(1 << self.GPIO_RESET_CONFIG_POS) & self._gpio_ctrl.read())

    def reset_config_off(self):
        """Deactivate reset pin ICE_RESET"""
        self._gpio_ctrl.write((1 << self.GPIO_RESET_LOGIC_POS) | self._gpio_ctrl.read())

    def close_connection(self):
        """Close FTDI interface"""
        self._spi_ctrl.terminate()
        self._gpio_ctrl.close()

if __name__ == "__main__":
    Ftdi.show_devices()