'''
Tests of external Asynchronous Static RAM.
Tests are automatic - RAM is filled with specified pattern by hardware,
then whole memory are read, then check if values match, repeat for other pattern.
'''
from time import time, sleep
from random import randint
from fpga_ctrl import FpgaControl

QUIET_VERIFY = True # change this setting carefully - verify will take much more time if disabled
MAX_LINES = 32
WORDS_PER_LINE = 16384

def verify(golden, revised):
    ram_addr = 0
    err_cnt = 0
    for l in range(MAX_LINES):
        print("\tLines %d match:" % l, golden[l] == revised[l])
        for w in range(WORDS_PER_LINE):
            # iterate through lines and words inside
            gw = golden[l][w]
            rw = revised[l][w]
            w_str = "ram_addr=0x%05x, line=%02d, word=%05d, golden=0x%04x, revised=0x%04x" % (ram_addr, l, w, gw, rw)
            if (not QUIET_VERIFY):
                print("\t%s" % w_str)
            if (gw != rw):
                print("\tError! %s" % w_str)
                err_cnt += 1
            ram_addr += 1
    return err_cnt

if __name__ == "__main__":
    fpga = FpgaControl('ftdi://ftdi:2232:/', spi_freq=8E6)
    fpga.reset()

    err_cnt = 0

    print("Test RAM read time ...")
    start_time = time()
    fpga.read_lines(MAX_LINES)
    end_time = time()
    print("\t full RAM reading is done in %f seconds." % (end_time - start_time))

    print("Test with incrementing data pattern ...")
    # Fill RAM with incrementing data pattern
    fpga.csr.ramfinc = 1
    while (not fpga.csr.ramfdone):
        sleep(0.01)
    # Get data from RAM
    revised = fpga.read_lines(MAX_LINES)
    # Prepare golden data
    golden_data = 0
    golden = []
    for l in range(MAX_LINES):
        line = []
        for w in range(WORDS_PER_LINE):
            line += [golden_data & 0xFFFF]
            golden_data += 1
        golden += [line]
    # Verify
    err_cnt += verify(golden, revised)

    print("Test with decrementing data pattern ...")
    # Fill RAM with decrementing data pattern
    fpga.csr.ramfdec = 1
    while (not fpga.csr.ramfdone):
        sleep(0.01)
    # Get data from RAM
    revised = fpga.read_lines(MAX_LINES)
    # Prepare golden data
    golden_data = 0xFFFFFFF
    golden = []
    for l in range(MAX_LINES):
        line = []
        for w in reversed(range(WORDS_PER_LINE)):
            line += [golden_data & 0xFFFF]
            golden_data -= 1
        golden += [line]
    # Verify
    err_cnt += verify(golden, revised)
    if (err_cnt):
        print("Test FAIL: %d errors!" % err_cnt)
    else:
        print("Test OK!")

    fpga.reset()
    fpga.disconnect()
