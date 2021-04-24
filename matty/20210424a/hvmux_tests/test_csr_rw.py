'''
Tests of RW registers.
Tests are automatic - write random value, then read current state, check if values match
'''
from random import randint
from fpga_ctrl import FpgaControl

QUIET_VERIFY = True


def verify(golden, revised):
    if (not QUIET_VERIFY):
        print("\tgolden", golden)
        print("\trevised", revised)
    if (golden == revised):
        return 0
    else:
        if (isinstance(golden, list)):
            print("Error! Expected\n", golden, "\nbut got\n", revised)
        else:
            print("Error! Expected 0x%x, but got 0x%x" % (golden, revised))
        return 1


if __name__ == "__main__":
    fpga = FpgaControl('ftdi://ftdi:2232:/', spi_freq=8E6)
    fpga.reset()

    test_iter = 100
    err_cnt = 0

    print("INITDEL test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.INITDEL_MASK)
        fpga.csr.initdel = golden
        revised = fpga.csr.initdel
        err_cnt += verify(golden, revised)

    print("PONW test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.PONW_MASK)
        fpga.csr.ponw = golden
        revised = fpga.csr.ponw
        err_cnt += verify(golden, revised)

    print("POFFW test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.POFFW_MASK)
        fpga.csr.poffw = golden
        revised = fpga.csr.poffw
        err_cnt += verify(golden, revised)

    print("INTERW test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.INTERW_MASK)
        fpga.csr.interw = golden
        revised = fpga.csr.interw
        err_cnt += verify(golden, revised)

    print("DRMODE test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.DRMODE_MASK)
        fpga.csr.drmode = golden
        revised = fpga.csr.drmode
        err_cnt += verify(golden, revised)

    print("DACOUT test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.DACOUT_MASK)
        fpga.csr.dacout = golden
        revised = fpga.csr.dacout
        err_cnt += verify(golden, revised)

    print("DACGAIN test ...")
    for i in range(test_iter):
        golden = [randint(0, fpga.csr.DACGAIN_MASK)
                  for w in range(fpga.csr.DACGAIN_N)]
        fpga.csr.dacgain = golden
        revised = fpga.csr.dacgain
        err_cnt += verify(golden, revised)

    print("NBLINES test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.NBLINES_MASK)
        fpga.csr.nblines = golden
        revised = fpga.csr.nblines
        err_cnt += verify(golden, revised)

    print("LED1 test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.LED1_MASK)
        fpga.csr.led1 = golden
        revised = fpga.csr.led1
        err_cnt += verify(golden, revised)

    print("LED2 test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.LED2_MASK)
        fpga.csr.led2 = golden
        revised = fpga.csr.led2
        err_cnt += verify(golden, revised)

    print("LED3 test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.LED3_MASK)
        fpga.csr.led3 = golden
        revised = fpga.csr.led3
        err_cnt += verify(golden, revised)

    print("OUT1ICE test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.OUT1ICE_MASK)
        fpga.csr.out1ice = golden
        revised = fpga.csr.out1ice
        err_cnt += verify(golden, revised)

    print("OUT2ICE test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.OUT2ICE_MASK)
        fpga.csr.out2ice = golden
        revised = fpga.csr.out2ice
        err_cnt += verify(golden, revised)

    print("OUT3ICE test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.OUT3ICE_MASK)
        fpga.csr.out3ice = golden
        revised = fpga.csr.out3ice
        err_cnt += verify(golden, revised)

    print("HVMUXEN test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.HVMUXEN_MASK)
        fpga.csr.hvmuxen = golden
        revised = fpga.csr.hvmuxen
        err_cnt += verify(golden, revised)

    print("HVMUXSW test ...")
    for i in range(test_iter):
        golden = randint(0, fpga.csr.HVMUXSW_MASK)
        fpga.csr.hvmuxsw = golden
        revised = fpga.csr.hvmuxsw
        err_cnt += verify(golden, revised)

    if (err_cnt):
        print("Test FAIL: %d errors!" % err_cnt)
    else:
        print("Test OK!")
    fpga.reset()
    fpga.disconnect()
