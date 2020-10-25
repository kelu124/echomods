#!/usr/bin/python3
from smbus2 import i2c_msg
import numpy as np
import pyaudio
import threading
import math

class py_fpga:
    __signal_size = 8192
    __fft_size = 256
    __spi_max_speed_hz = 1000000
    __CHUNK = 2**10
    __FORMAT = pyaudio.paInt16
    __CHANNELS = 2
    __RATE = 48000
    __RECORD_SECONDS = 0.10


    def __init__(self, i2c_bus, spi_bus=None, py_audio=None, i2c_dev_addr=0x25):
        self.__i2c_dev_addr = i2c_dev_addr
        self.__i2c_bus = i2c_bus
        self.__spi_bus = spi_bus
        self.__py_audio = py_audio
        self.__i2s_header = np.array([i for i in range(32)], dtype=np.uint8)

        if self.__spi_bus != None:
            self.__spi_bus.max_speed_hz = self.__spi_max_speed_hz
        
        self.i2c_write(8, 0)

    def i2c_write(self, addr, data):
        _data = [(data >> i*8) & 0xFF for i in range(4)]
        _data.reverse()
        _addr = [(addr >> i*8) & 0xFF for i in range(2)]
        _addr.reverse()
        # print(_addr)
        # print(_data)
        wr = i2c_msg.write(self.__i2c_dev_addr, _addr + _data)
        # print(f'Write data {data} into into register with addr {addr}')
        self.__i2c_bus.i2c_rdwr(wr)

    def i2c_read(self, addr):
        _addr = [(addr >> i*8) & 0xFF for i in range(2)]
        _addr.reverse()
        wr = i2c_msg.write(self.__i2c_dev_addr, _addr)
        rd = i2c_msg.read(self.__i2c_dev_addr, 4)
        self.__i2c_bus.i2c_rdwr(wr, rd)
        data = list(rd)
        rez = 0
        for i in range(len(data)):
            rez |= (data[i] & 0xFF) << (i * 8)
        return rez

    def set_dac(self, val, channel='A', gain=1, shutdown=0, mem=None):
        """ The function for setup DAC value
        Parameters val, channel, and gain setup the DAC value, channel for write and gain respectivelly
        Parameter shutdown perform shutdown mode of the DAC
        Parameter mem setup the memory cell for the DAC values during acquisition
        For setup the common DAC value (which applyes not during acquisition) type Nono into the mem parameter or dont initialize it
        For setup one of memory cells for the DAC value during acquisition set into mem parameter a cell address
        Cells into memory have a word addressing from 0 to 15. 
        These 16 values will applied during acquisition sequentially from 0 to 15 after the constant period (512 samples)
        """
        
        tmp = 0
        tmp = (val & (2**10-1)) << 2 # do a shift, because we have 10 bit ADC, but 12 bit ADC compatible register
        if channel == 'A':
            tmp &= ~(1 << 15) # clear the channel bit for select channel A
        else:
            tmp |= (1 << 15) # setup the channel bit for select channel B
        if gain == 1:
            tmp |= (1 << 13)
        if shutdown == 0:
            tmp |= (1 << 12)
        if mem == None:
            self.i2c_write(16, tmp)
        else:
            self.i2c_write(24, ((mem & 0xFF) << 16) | tmp)

    def set_waveform(self, pdelay = 1, PHV_time = 1, PnHV_time = 1, PDamp_time = 1):
        print("Waveform: ",pdelay,PHV_time,PnHV_time,PDamp_time)
        self.i2c_write(8 << 2, np.uint32(pdelay))
        self.i2c_write(9 << 2, np.uint32(PHV_time))
        self.i2c_write(10 << 2, np.uint32(PnHV_time))
        self.i2c_write(11 << 2, np.uint32(PDamp_time))

    def set_HILO(self, val):
        # tmp = self.i2c_read(8)
        # tmp |= ((val & 0x1) << 24)
        self.i2c_write(20, val & 0x1)

    def read_signal_through_spi(self):
        signal = bytes(0)
        
        self.i2c_write(8, 3 << 8)
        for j in range(self.__signal_size//1024):
            addr = []
            for i in range(j * 1024, j * 1024 + 1025, 1):
                addr += [(i >> 8) & 0xFF, i & 0xFF]

            result = self.__spi_bus.xfer2(addr)
            signal += bytes(result[2:])

        signal = np.frombuffer(signal, dtype=np.int16)
        return signal
    
    def read_signal_through_i2c(self):
        signal = bytes(0)
        values = []
        # print(f'Start reading through I2C')

        import time
        
        self.i2c_write(8, 2 << 8)

        for i in range(self.__signal_size):
            tmp = i * 4
            addr = [(tmp >> 8) & 0xFF | 0x80, tmp & 0xFF]
            wr = i2c_msg.write(self.__i2c_dev_addr, addr)
            rd = i2c_msg.read(self.__i2c_dev_addr, 4)
            self.__i2c_bus.i2c_rdwr(wr, rd)
            tmp = list(rd)[1] << 8 | list(rd)[0]
            values.append(tmp)
            signal += bytes(tmp.to_bytes(2, byteorder='little'))
        
        # print(f'Minimal value = {min(values)} | Maximum value = {max(values)} | Average value = {sum(values)//len(values)}')
        signal = np.frombuffer(signal, dtype=np.int16)
        return signal

    def wrtie_signal_through_i2c(self, signal):
        assert len(signal) == self.__signal_size, (f'Incorrect signal size!'
                                                 f'Expected {self.__signal_size}, received {len(signal)}')
        self.i2c_write(8, 2 << 8)
        for i in range(self.__signal_size):
            tmp = ((signal[i] >> 24) & 0xFF) | (((signal[i] >> 16) & 0xFF) << 8) | (((signal[i] >> 8) & 0xFF) << 16) | (((signal[i] >> 0) & 0xFF) << 24)
            self.i2c_write(i << 2 | 1 << 15, tmp)
    
    def read_fft_through_i2c(self):
        fft_data = np.ndarray(self.__fft_size, dtype=np.int32)

        self.i2c_write(8, 2 << 16)
        for i in range(self.__fft_size):
            fft_data[i] = self.i2c_read((i << 2 | 1 << 15))

        return fft_data

    def read_fft_through_spi(self):
        signal = bytes(0)
        self.i2c_write(8, 3 << 16)
        addr = []
        for i in range(self.__fft_size + 1):
            addr += [(i >> 8) & 0xFF, i & 0xFF]
        result = self.__spi_bus.xfer2(addr)
        signal += bytes(result[2:])
        signal = np.frombuffer(signal, dtype=np.int16)
        return signal

    def read_fft_through_i2s(self, count):
        ms = count * 1.5
        self.i2c_write(8, 1 << 4)
        frames = self.__capture(ms)
        self.i2c_write(8, 1 << 8)
        frames = [x for sublist in frames for x in sublist]
        data = self.__align_data(frames)
        tmp = data.copy()
        j = 0
        i = 0
        data = np.zeros(len(tmp)//2)
        while i + 512 < len(tmp):
            data[j : j + 256] = tmp[i + 256 : i + 512]
            j += 256
            i += 512
        return data[:count*256]

    def __read_signal_through_i2s(self):
        raise "Not supported into the hardware!"
        self.i2c_write(8, 1 << 8)
        frames = self.__capture(self.__RECORD_SECONDS)
        data = self.__align_data(frames)
        return data[32:8192+32]

    def capture_signal(self):
        self.i2c_write(8, 8)
        # self.i2c_write(8, 0)

    def calc_fft(self):
        self.i2c_write(8, 4 << 16 | 4 << 8 | 1)
        self.i2c_write(8, 4 << 16 | 4 << 8 | 0)
        tmp = self.i2c_read(12)
        print("test")
        while((tmp & 0x1) != 0):
            # print(tmp)
            tmp = self.i2c_read(12)
            print("test")
            pass

    def __align_data(self, frames):
        data = np.copy(np.array(frames, dtype=np.uint8))
        data[0:-1:2] = data[0:-1:2] ^ data[1::2]
        data[1::2] = data[0:-1:2] ^ data[1::2]
        data[0:-1:2] = data[0:-1:2] ^ data[1::2]
        tmp = data

        # print(self.i2c_read(12))
        # print(tmp[0:256])

        idx = np.where(tmp == 0x00)
        if len(idx[0]) != 0:
            idx = idx[0][0]
        else:
            idx = 0
        # print(list(map(hex, tmp[idx:idx+512:1])))
        while not (tmp[idx:idx+32:1] == self.__i2s_header).all():
            tmp = ((data[:-1] & 0x7F) << 1) | ((data[1:] >> 7) & 0x01)
            # print(f'Original data = 0x{data[2]:02x} 0x{data[1]:02x}')
            # print(f'Shifted data = 0x{tmp[1]:02x} 0x{tmp[0]:02x}')
            idxs = np.where(tmp == 0x00)[0]
            idx = -1
            for i in idxs:
                if i + 32 < len(tmp):
                    if (tmp[i:i+32:1] == self.__i2s_header).all():
                        idx = i
                        break

            if idx == -1:
                idx = 0
                
            data = tmp

        data = tmp[idx:]
        return data

    def __capture(self, ms):
        stream = self.__py_audio.open(format=self.__FORMAT,
                        channels=self.__CHANNELS,
                        rate=self.__RATE,
                        input=True,
                        frames_per_buffer=self.__CHUNK, 
                        input_device_index=1)

        print("* recording")

        frames = []

        for i in range(0, int(math.ceil(self.__RATE * self.__CHANNELS / self.__CHUNK * ms / 1000))):
            data = stream.read(self.__CHUNK)
            # print(data)
            frames.append(list(data))

        #print("* done recording")

        stream.stop_stream()
        stream.close()
        self.__py_audio.terminate()
        return frames
