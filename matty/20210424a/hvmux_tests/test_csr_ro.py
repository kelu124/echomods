'''
Tests of RO registers.
Tests are semi-automatic - you need to change state of the external pins mannually,
and then read out all values and check if they match
'''
from fpga_ctrl import FpgaControl

if __name__ == "__main__":
    fpga = FpgaControl('ftdi://ftdi:2232:/', spi_freq=8E6)
    fpga.reset()

    print("TOPTURN1 = 0x%x" % fpga.csr.topturn1)
    print("TOPTURN2 = 0x%x" % fpga.csr.topturn2)
    print("TOPTURN3 = 0x%x" % fpga.csr.topturn3)

    print("JUMPER1 = 0x%x" % fpga.csr.jumper1)
    print("JUMPER2 = 0x%x" % fpga.csr.jumper2)
    print("JUMPER3 = 0x%x" % fpga.csr.jumper3)

    print("AUTHOR = 0x%x" % fpga.csr.author)
    print("VERSION = 0x%x" % fpga.csr.version)

    fpga.reset()
    fpga.disconnect()
