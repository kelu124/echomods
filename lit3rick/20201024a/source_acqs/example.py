#!/usr/bin/python3

from pathlib import Path
from random import randint
from smbus2 import SMBus
from py_fpga import py_fpga
import time
import numpy as np
import spidev
import dft
import alaw
import us_display as viz
import matplotlib.pyplot as plt
from ctypes import *
from contextlib import contextmanager
import pyaudio

ERROR_HANDLER_FUNC = CFUNCTYPE(None, c_char_p, c_int, c_char_p, c_int, c_char_p)

def py_error_handler(filename, line, function, err, fmt):
    pass

c_error_handler = ERROR_HANDLER_FUNC(py_error_handler)

@contextmanager
def noalsaerr():
    asound = cdll.LoadLibrary('libasound.so')
    asound.snd_lib_error_set_handler(c_error_handler)
    yield
    asound.snd_lib_error_set_handler(None)

def registers_test():
    test_data = []
    for i in range(4):
        test_data.append(randint(0, 2**32))
        fpga.i2c_write(i << 2, test_data[i])

    for i in range(4):
        tmp = fpga.i2c_read(i << 2)
        assert test_data[i] == tmp, (f'Readed incorrect value from register {i}')

    for i in range(4):
        fpga.i2c_write(i << 2, 0)

    print(f'Registers test passed!')

def test_i2c_acces_to_signal_ram(signal):
    print("\n- Testing i2c access to signal.. ")
    read_signal = fpga.read_signal_through_i2c()
    assert all(signal == read_signal), (f'readed signal not equal with written signal!')
    print(read_signal)
    print(f'I2C access to signal ram test passed!')

def test_spi_access_to_signal_ram(signal):
    print("\n- Testing SPI access to signal.. ")
    read_signal = fpga.read_signal_through_spi()
    assert all(signal == read_signal), (f'readed signal not equal with written signal!')
    print(read_signal)
    print(f'SPI access to signal ram test passed!')

def test_i2s_access_to_signal_ram(signal):
    signal = signal >> 4
    signal = np.uint8(signal)
    print("\n- Testing i2s access to signal (on 8bits though).. ")
    read_signal = fpga.read_signal_through_i2s()
    assert all(signal == read_signal), (f'readed signal not equal with written signal!')
    print(read_signal)
    print(f'i2s access to signal space test passed!')

def fill_signal():
    signal = gen_signal()
    signal = (np.genfromtxt("ref.data", delimiter=';')/2).astype(int)
    signal = signal
    print(signal)
    fpga.wrtie_signal_through_i2c(signal)
    return signal

def test_fft(signal):

    print("\n- Testing onboard Enveloppe extraction..")
    fpga.calc_fft()
    print(f"Enveloppe calculated")
    fpga_fft = fpga.read_fft_through_spi()
    print(f"Enveloppe read from SPI.")
    print(f"Local calculation of enveloppe. ")
    tmp = signal.reshape(256, -1)
    ref_fft = dft.dft_python_model(tmp)
    ref_fft = alaw.alaw_compress(ref_fft)

    print(fpga_fft[1:])

    plt.figure(figsize = (15,5))
    plt.plot(ref_fft[1:])
    plt.title("Testing ref data") 
    viz.checkFolder("images")
    plt.savefig("images/refdata_fpga_enveloppe.png")

    plt.figure(figsize = (15,5))
    plt.plot(fpga_fft[1:])
    plt.title("Testing ref data") 
    viz.checkFolder("images")
    plt.savefig("images/refdata_calculated_enveloppe.png")

    plt.figure(figsize = (15,5))
    plt.plot(signal)
    plt.title("Testing ref data") 
    viz.checkFolder("images")
    plt.savefig("images/refdata.png")

    print(f'Onboard Enveloppe extraction processing test passed!')

def gen_signal():
    signal = np.ndarray(8192, dtype=np.uint16)
    for i in range(len(signal)):
        # signal[i] = randint(0, 1023) & 0xFFF
        signal[i] = i & 0xFFF
    return signal


def testAll():
    print("\n- Filling in the memory.. ") 
    signal = fill_signal()
    test_i2c_acces_to_signal_ram(signal)
    test_spi_access_to_signal_ram(signal)
    test_i2s_access_to_signal_ram(signal)
    test_fft(signal)


if __name__ == "__main__":
    i2c_bus = SMBus(1)
    spi = spidev.SpiDev()
    spi.open(0,0)
    p = None
    with noalsaerr():
        p = pyaudio.PyAudio()
    p = pyaudio.PyAudio()

    # Starting an object 
    fpga = py_fpga(i2c_bus=i2c_bus, py_audio=p, spi_bus=spi)
    # Setting up the pulse 
    fpga.set_waveform(pdelay=1, PHV_time=15, PnHV_time=17, PDamp_time=7)

    print("Setting DAC")
    startVal,nPtsDAC = 250, 16
    for i in range(nPtsDAC):
        fpga.set_dac(int(startVal + (i*(455-startVal))/nPtsDAC), mem=i)

    fpga.set_dac(0, mem=0)
    fpga.set_dac(0, mem=1)
    fpga.set_dac(0, mem=2)

    hiloVal = 1
    dacVal = 100
    fpga.set_HILO(hiloVal)
    fpga.set_dac(dacVal)
    print("Reading signal through i2s")
    # fpga.capture_signal()
    data = fpga.read_fft_through_i2s(4000)  
    np.savetxt('10k.csv', data, delimiter=",")
    print("Acq done")
    fig = plt.figure(figsize=(15,5))
    fig = plt.plot(data)
    plt.savefig("10k_i2s_test.png")   
    print("I2S done")
    time.sleep(3/1000.0)
    print("Reading through spi")
    data = fpga.read_signal_through_spi()
    fig = plt.figure(figsize=(15,5))
    fig = plt.plot(data)
    plt.savefig("10k_raw_ref.png")   


    if 1:
        print("Starting FFT calc")
        fpga.calc_fft() 
        time.sleep(3/1000.0)
        fpga_fft = fpga.read_fft_through_spi()
        print("FFT obtained")
        fig = plt.figure(figsize=(15,5))
        fig = plt.plot(fpga_fft)
        plt.savefig("10k_fpga_fft.png")   
