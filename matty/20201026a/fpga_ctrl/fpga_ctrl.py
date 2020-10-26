'''
Main FPGA control script
'''

from time import sleep
from csr_map import CsrMap
from ftdi_dev import FtdiDevice

class FpgaControl(object):
    """Collection of FPGA control functions via FTDI API"""
    MAX_LINES = 32
    WORDS_PER_LINE = 16384

    def __init__(self, ftdi_url, spi_freq=1E6):
        """Initialize FPGA controller.

        Keyword arguments:
         ftdi_url -- FTDI device url, which can be obtained by Ftdi.show_devices()
         freq -- SPI frequency up to 8E6 (for FPGA running on 64 MHz)
        """
        self._ftdi = FtdiDevice(ftdi_url, spi_freq)
        self.csr = CsrMap(self._ftdi)

    def reset(self):
        """Reset FPGA logic"""
        self._ftdi.reset_logic_on()
        sleep(0.01)
        self._ftdi.reset_logic_off()

    def reload(self):
        """Reload FPGA configuration from flash"""
        self._ftdi.reset_config_on()
        sleep(0.01)
        self._ftdi.reset_config_off()
        sleep(0.5)

    def read_lines(self, n):
        """Read 'n' number of lines from SRAM buffer

        Maxinum 'n' -- 32
        """
        # reset external ram address to read from the memory beginning
        self.csr.ramraddrrst = 1
        res = []
        for _ in range(n):
            # read lines (16384 words per line) one by one
            line = self.csr.ramdata
            res += [line]
        return res

    def do_acquisition(self, acq_lines=1, gain=None, double_rate=False):
        """Do acquisitions.
        
        Keyword arguments:
          acq_lines -- number of lines to sample: int 1 .. 32
          gain -- list with gain values: None or list with length of 32
          double_rate -- enable/disable interleaving mode: bool
        """
        if gain:
            self.csr.dacgain = gain
        self.csr.nblines = acq_lines - 1
        self.csr.drmode = int(double_rate)
        self.csr.acqstart = 1
        while (not self.csr.acqdone):
            sleep(0.01)
        return self.read_lines(acq_lines)

    def disconnect(self):
        """Disconnect from FTDI and close all open ports"""
        self._ftdi.close_connection()

if __name__ == "__main__":
    # init FTDI device
    fpga = FpgaControl('ftdi://ftdi:2232:/', spi_freq=8E6)

    # reload configuration (optional step - just to fill BRAM (DACGAIN registers) with initial values)
    fpga.reload()

    # reset fpga
    fpga.reset()

    # read initial state of INITDEL register
    print("initdel = 0x%x" % fpga.csr.initdel)
    # write new value to the INITDEL
    fpga.csr.initdel = 0x20
    # read current state of INITDEL register
    print("initdel = 0x%x" % fpga.csr.initdel)

    # read DACGAIN array initial state
    print("dacgain = ", fpga.csr.dacgain)
    # write new values to the DACGAIN
    fpga.csr.dacgain = [200 + i for i in range(32)]
    # read DACGAIN array current state
    print("dacgain = ", fpga.csr.dacgain)

    # some LED3 blinking
    fpga.csr.led3 = 1
    sleep(1)
    fpga.csr.led3 = 0
    sleep(0.3)
    fpga.csr.led3 = 1
    sleep(0.3)
    fpga.csr.led3 = 0

    # reset fpga again (optional)
    fpga.reset()

    # close FTDI interface
    fpga.disconnect()
