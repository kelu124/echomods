# -*- coding: utf-8 -*-
"""
Description: Most updated library for the lit3rick platform.
`20190407a`
@todo: improve doc: http://sametmax.com/les-docstrings/
"""

__author__ = "kelu124"
__copyright__ = "Copyright 2018, Kelu124"
__license__ = "GPLv3"

import json
import time
import datetime
import os
import glob
import sys
import re
import spidev
import numpy as np
import matplotlib.pyplot as plt

try:
    import RPi.GPIO as GPIO
except:
    print("Not loading RPi.GPIO as not on RPi")
    gpioexists = False
else:
    gpioexists = True

try:
    import pyexiv2
except:
    print("pyexiv2 does not exist on RPi")
    pyexivexists = False
else:
    pyexivexists = True


##############
#
# RPI Part
#
##############

class SpiConnector:
    """
       Creates a connection to the board.
       Used to acquire signals and store all acquisition parameters.
    """

    JSON = {}
    spi = spidev.SpiDev()

    JSON["firmware_md5"] = "fa6a7560ade6d6b1149b6e78e0de051f"
    JSON["firmware_version"] = "e_un0"
    JSON["data"] = []
    JSON["time"] = str(datetime.datetime.now())
    JSON["registers"] = {}
    JSON["registersHex"] = {}
    JSON["experiment"] = {}
    JSON["parameters"] = {}
    JSON["timings"] = {}
    JSON["experiment"]["id"] = str(datetime.datetime.now().strftime("%Y%m%d"))+"a"
    JSON["experiment"]["description"] = "na"
    JSON["experiment"]["probe"] = "na"
    JSON["experiment"]["target"] = "na"
    JSON["experiment"]["position"] = "na"
    JSON["V"] = "-1"

    f_ech = 0
    Nacq = 0
    LAcq = 0
    number_lines = 0
    verbose = True

    def create_tgc_curve(self, init_value, final_value, curve_type):
        """
        Returns an array with the TGC values, along a 40 values array.
        Used afterwards to set FPGA registers.
        """
        n = int(200/5)
        dac_array = []
        for k in range(n + 1):
            if curve_type:
                val = int(init_value + 1.0*k*(final_value-init_value)/n)
            else:
                val = int((final_value - init_value)*k**3/n**3 + init_value)
            dac_array.append(val)
        dac_array[-1] = 0
        dac_array[-2] = 0
        self.set_tgc_curve(dac_array)
        return dac_array, len(dac_array)

    def set_timings(self, p_on, p_damp_one, p_HV_neg, p_off, delay_acq, acq):
        """
        Programs the sequence of Pon, Poff, Acquisition.
        """
        # t4 = WaitTill # 20us delay before acquisition
        # Pon, PdampOne, PHVneg, Poff, delay_acq, Acq
        # self.set_pulse_train(t1, t2, t3, t4, t5)
        self.set_pulse_train(p_on, p_damp_one, p_HV_neg, p_off, delay_acq, acq)
        # Some figures about the acquisitions now
        self.LAcq = (acq - delay_acq)/1000    # ns to us
        self.Nacq = int(self.LAcq * self.f_ech * self.number_lines)
        self.JSON["timings"]["t1"] = p_on
        self.JSON["timings"]["t2"] = p_damp_one
        self.JSON["timings"]["t3"] = p_HV_neg
        self.JSON["timings"]["t4"] = p_off
        self.JSON["timings"]["t5"] = delay_acq
        self.JSON["timings"]["t5"] = acq
        self.JSON["timings"]["NAcq"] = self.Nacq
        self.JSON["timings"]["LAcq"] = self.LAcq
        self.JSON["timings"]["Fech"] = self.f_ech
        self.JSON["timings"]["NLines"] = self.number_lines

        print("NAcq = "+str(self.Nacq))
        if self.Nacq > 199999:
            raise NameError('Acquisition length over 200.000 points (8Mb = Flash limit)')
        return self.Nacq, self.LAcq, self.f_ech, self.number_lines

    def set_multi_lines(self, set_multi):    # OK LIT3RICK
        """
        Determines if this is a single-line of multi-line acquisition.
        """
        if set_multi:
            if self.verbose:
                print("Doing several lines."
                      "\nRemember to indicate how many lines. number_lines = 3 by default")
            self.write_fpga(0xEB, 1)    # Doing one line if 0, several if 1
            self.number_lines = 3
        else:
            if self.verbose:
                print("Doing a single line")
            self.write_fpga(0xEB, 0)    # Doing one line if 0, several if 1
            self.number_lines = 1

    def set_tgc_curve(self, tgc_values):    # OK LIT3RICK
        """
        Sets up the TGC using an array
        """
        # Print "Setting up the DAC curves"
        if len(tgc_values) < 43:    # to correct
            for i in range(len(tgc_values)):
                if (tgc_values[i] >= 0) and (tgc_values[i] < 1020):
                    self.write_fpga(16 + i, tgc_values[i]/4)  # /4 since 1024 values, on 8 bits
                else:
                    self.write_fpga(16 + i, 0)

    """
    FPGA controls.
    """

    def write_fpga(self, address, value):   # OK LIT3RICK
        """
        Basic function to write registers value to the FPGA
        """
        if gpioexists:
            self.spi.xfer([0xAA])
            self.spi.xfer([address])
            self.spi.xfer([value])
        self.JSON["registersHex"][hex(address)] = hex(value)
        self.JSON["registers"][int(address)] = value

    def set_led_rgb(self, red, gren, blue):
        self.write_fpga(0xC1, red)
        self.write_fpga(0xC2, gren)
        self.write_fpga(0xC3, blue)

    def init(self):  # OK LIT3RICK
        """
        Initialises the FPGA
        """
        if gpioexists:
            GPIO.setmode(GPIO.BCM)
            # Once program is loaded, should be OK
            # for k in [3,4,17,27,5,12,16,20,15]:
            # GPIO.setup(k, GPIO.IN)
            # @todo: reset from flash when flash works
            self.spi.open(0, 0)  # CS0 is the FPGA, CS1 is flash
            self.spi.mode = 0b01
            self.spi.max_speed_hz = 500000
            if self.verbose:
                print("spi.cshigh is " + str(self.spi.cshigh))
                print("spi mode is " + str(self.spi.mode))
                print("spi maxspeed is "+str(self.spi.max_speed_hz) + "hz")
            self.set_led_rgb(0, 1, 0)
        else:
            print("Not running from a Raspberry Pi")

    """
    Testing functions
    """

    def test_spi(self, n_cycles):   # OK LIT3RICK
        """
        Blinks the HILO n_cycles times.
        """
        self.set_led_rgb(0, 0, 1)

    def set_hilo(self, hilo):  # OK LIT3RICK
        """
        Sets HILO on TGC
        """
        if hilo:
            self.write_fpga(0xD8, 0x01)  # 1: HILO ON
            print("HILO set HIGH")
        else:
            self.write_fpga(0xD8, 0x00)  # 0: HILO OFF
            print("HILO set LOW")

    def loop_spi(self):  # OK LIT3RICK
        """
        Pure debug test to spam SPI bus to have HILO LED blink continuously
        """
        while 1:
            self.write_fpga(0xD8, 0x01) 
            self.write_fpga(0xD8, 0x00) 

    def loop_acq(self):  # OK LIT3RICK
        """
        Pure debug test to spam SPI bus with loop acquisition.
        """
        while 1:
            self.write_fpga(0xEB, 0x00)  # Doing 1 shot
            self.write_fpga(0xEF, 0x01)  # Cleaning memory pointer
            self.write_fpga(0xEA, 0x0)   # Software Trig : As to be clear by software
            time.sleep(0.001)            # sleep 1ms

    def clear_mem(self):  # OK LIT3RICK
        """
        Reset RAM pointer
        """
        self.write_fpga(0xEF, 0x01)  # To access memory

    """
    Setup functions
    """
    def set_msps(self, f_msps):
        """
        Setting acquisition speed.
        Using F, ADC speed is determined as 64Msps / (1 + f_msps)
        """
        self.write_fpga(0xED, f_msps)
        self.f_ech = float(64/(1 + f_msps))
        print("Acquisition frequency set at "+str(self.f_ech) + " Msps")
        return self.f_ech

    def do_acquisition(self):
        """
        Doing an acquisition, trigs, then reads the data.
        """
        self.write_fpga(0xEF, 0x01)  # Cleaning memory pointer
        self.JSON["time"] = str(datetime.datetime.now())
        self.write_fpga(0xEA, 0x01)  # Software Trig : As to be clear by software
        self.JSON["data"] = []
        time.sleep(1)
        milestone = self.Nacq / 5
        start = time.time()
        if gpioexists:
            for i in range(2*self.Nacq+2):
                self.JSON["data"].append(self.spi.xfer([0x00])[0])
                if not ((i+10) % milestone) and self.verbose:
                    print(str((50*i)/self.Nacq)+"% - "+str(self.JSON["data"][-1])+" & "+str(self.JSON["data"][-2]))
            end = time.time()
            delta = end - start
            if self.verbose:
                print("Took %.2f seconds to transfer." % delta)
                print("for "+str(2*self.Nacq+2)+" transfers of data")
            self.JSON["N"] = new_n("./",self.JSON["experiment"]["id"])
            name_json = self.JSON["experiment"]["id"]+"-"+str(self.JSON["N"])+".json"
            with open(name_json, 'w') as outfile:
                json.dump(self.JSON, outfile)
            self.JSON["data"] = []
            self.write_fpga(0xEF, 0x01)  # Cleaning memory pointer
            self.set_led_rgb(0, 0, 1)
            for i in range(2*self.Nacq+2):
                self.JSON["data"].append(self.spi.xfer([0x00])[0])
            name_json = "_"+self.JSON["experiment"]["id"]+"-"+str(self.JSON["N"])+".json"
            with open(name_json, 'w') as outfile:
                json.dump(self.JSON, outfile)
            if self.verbose:
                print(name_json+": file saved.")
        else:
            print("Not on a RPI")
        return self.JSON["data"]

    def do_acquisition_twice(self):
        """
        Doing an acquisition, trigs, then reads the data.
        """
        self.write_fpga(0xEF, 0x01)  # Cleaning memory pointer
        self.JSON["time"] = str(datetime.datetime.now())
        self.write_fpga(0xEA, 0x01)  # Software Trig : As to be clear by software
        self.JSON["data"] = []
        time.sleep(1)
        milestone = self.Nacq / 5
        start = time.time()
        if gpioexists:
            for i in range(2*self.Nacq + 2):
                self.JSON["data"].append(self.spi.xfer([0x00])[0])
            if not ((i+10) % milestone) and self.verbose:
                print(str((50*i)/self.Nacq)+"% - "+str(self.JSON["data"][-1])+" & "+str(self.JSON["data"][-2]))
            end = time.time()
            delta = end - start
            if self.verbose:
                print("Took %.2f seconds to transfer." % delta)
                print("for "+str(2*self.Nacq+2)+" transfers of data")
            self.JSON["N"] = new_n("./",self.JSON["experiment"]["id"])
            name_json = self.JSON["experiment"]["id"]+"a-"+str(self.JSON["N"])+".json"
            with open(name_json, 'w') as outfile:
                json.dump(self.JSON, outfile)
            if self.verbose:
                print(name_json+": file saved.")
        else:
            print("Not on a RPI")

        self.write_fpga(0xEF, 0x01)  # Cleaning memory pointer
        self.write_fpga(0xC2, 1)
        self.JSON["time"] = str(datetime.datetime.now())
        self.JSON["data"] = []
        time.sleep(1)
        milestone = self.Nacq / 5
        start = time.time()
        if gpioexists:
            for i in range(2*self.Nacq+2):
                self.JSON["data"].append(self.spi.xfer([0x00])[0])
            if not ((i+10)%milestone) and self.verbose:
                print(str((50*i)/self.Nacq) + "% - "+str(self.JSON["data"][-1])+" & "+str(self.JSON["data"][-2]))
            end = time.time()
            delta = end - start
            if self.verbose:
                print("Took %.2f seconds to transfer." % delta)
                print("for "+str(2*self.Nacq+2)+" transfers of data")
            self.JSON["N"] = new_n("./",self.JSON["experiment"]["id"])
            name_json = self.JSON["experiment"]["id"]+"b-"+str(self.JSON["N"])+".json"
            with open(name_json, 'w') as outfile:
                json.dump(self.JSON, outfile)
            if self.verbose:
                print(name_json+": file saved.")
        else:
            print("Not on a RPI")
        return self.JSON["data"]

    def set_acquisition_number_lines(self, n):
        """
        Sets the number of lines to acquire.
        """
        n_msb, n_lsb = n/256, 0x00FF & n
        self.write_fpga(0xEE, n_lsb)
        self.write_fpga(0xDE, n_msb)
        self.number_lines = n
        if self.verbose:
            print("Number of lines: " + str(n))

    def set_HV(self, hv_level):
        """
        Sets HV level
        """
        hv_msb, hv_lsb = hv_level/256, 0x00FF & hv_level
        self.write_fpga(0xD7, hv_lsb)
        self.write_fpga(0xD6, hv_msb)
        if self.verbose:
            print("HV Level: " + str(hv_level) + " (/1Obits)")

    def config_spi(self):
        """
        Initial configuration of the FPGA.
        """
        # Setup FPGA values by default
        self.set_pon(200)           # Set PulseOn
        self.set_pulses_delays()    # Set Lengh between Pon and Poff: 100ns
        self.set_poff(2000)         # Setting Poff 2us
        # set_tgc_constant(20, spi) # gain at 20mV (2%)
        self.write_fpga(0xEC, 0x33)  # Set DAC constant
        self.set_delta_acq(7000)     # 7us
        # write_fpga(0xEA, 0x00)     # Software Trig : As to be clear by software
        self.write_fpga(0xEB, 0x00)  # 0: single mode 1 continuous mode
        self.write_fpga(0xED, 0x03)  # Frequency of ADC acquisition
        self.set_acquisition_number_lines(0xA0)      # How many cycles in continuous mode
        print("Config FPGA done!")

    def set_tgc_constant(self, mv):
        """
        Setting TGC constant.
        """
        if mv > 1000:
            mv = 1000
        elif mv < 0:
            mv = 0
        hmv = int(mv/4)
        print("Gain:", mv, " mV -- ", hex(hmv))
        self.write_fpga(0xEC, hmv)  # Voltage gain control: 0V to 1V

    def set_pon(self, p_on):
        if p_on > 2500:
            p_on = 2500
        elif p_on < 0:
            p_on = 0
        unit_p_on = int(p_on * 128.0/1000)
        self.JSON["parameters"]["Pon"] = int(p_on)
        self.JSON["parameters"]["Pon_Real"] = int(unit_p_on * 1000/128)
        print("POn width:", p_on, " ns -- ", hex(unit_p_on))
        self.write_fpga(0xE0, unit_p_on)  # set sEEPon
        return unit_p_on * 1000/128

    def set_pon_neg(self, p_on_neg):
        if p_on_neg > 2500:
            p_on_neg = 2500
        elif p_on_neg < 0:
            p_on_neg = 0
        unit_p_on_neg = int(p_on_neg*128.0/1000)
        self.JSON["parameters"]["Pon_neg"] = int(p_on_neg)
        self.JSON["parameters"]["Pon_neg_Real"] = int(unit_p_on_neg * 1000/128)
        print("PonNeg width:", p_on_neg, " ns -- ", hex(unit_p_on_neg))
        self.write_fpga(0xD4, unit_p_on_neg)  # set sEEPon
        return unit_p_on_neg * 1000/128

    def set_p_damp_init(self, p_damp_init):
        if p_damp_init > 2500:
            p_damp_init = 2500
        elif p_damp_init < 0:
            p_damp_init = 0
        unit_p_damp_int = int(p_damp_init*128.0/1000)
        self.JSON["parameters"]["Pon_neg"] = int(p_damp_init)
        self.JSON["parameters"]["Pon_neg_Real"] = int(unit_p_damp_int*1000/128)
        print("PDampInt width:", p_damp_init, " ns -- ", hex(unit_p_damp_int))
        self.write_fpga(0xD2, unit_p_damp_int)  # set sEEPon
        return unit_p_damp_int*1000/128

    @staticmethod
    def set_pulses_delays():
        p_delay = int(10/(1000/128.0))
        return p_delay*1000/128

    def set_poff(self, poff_value):
        # Sets the damping length.
        p_off = int(poff_value / (1000/128.0))
        # print sEEPoff, POff
        p_off_msb, p_off_lsb = 0x00FF & int(p_off/256), 0x00FF & p_off
        print("Poff:", poff_value, " ns -- ", hex(p_off_msb), hex(p_off_lsb))
        self.JSON["parameters"]["Poff"] = int(poff_value)
        self.JSON["parameters"]["Poff_Real"] = int(p_off * 1000/128)
        self.write_fpga(0xE1, p_off_msb)  # set sEEPon MSB
        self.write_fpga(0xE2, p_off_lsb)  # set sEEPon LSB
        return p_off * 1000/128

    def set_delta_acq(self, acquisition_delay_val):
        """
        Setting Poff to Acq delay sEEDelayACQ
        """
        if acquisition_delay_val > 255*255:
            acquisition_delay_val = 254*254
        elif acquisition_delay_val < 0:
            acquisition_delay_val = 0
        hda = int((128*acquisition_delay_val)/1000.0)
        hda_msb, hda_lsb = int(hda/256), 0x00FF & hda
        print("Delay between:", hda*1000/128, "ns -- ", hex(hda_msb), hex(hda_lsb))
        self.JSON["parameters"]["DeltaAcq"] = int(acquisition_delay_val)
        self.JSON["parameters"]["DeltaAcq_Real"] = int(hda*1000/128)
        self.write_fpga(0xE3, hda_msb)  # set sEEPon MSB
        self.write_fpga(0xE4, hda_lsb)  # set sEEPon LSB
        return acquisition_delay_val

    def set_length_acq(self, LAcqI):
        correct_length_acq = int((128*LAcqI)/1000)  # (LAcqI*128/1000)
        # print correct_length_acq, hex(LAcq), hex(LAcqI)
        self.JSON["parameters"]["LengthAcq"] = int(LAcqI)
        self.JSON["parameters"]["LengthAcq_Real"] = int(correct_length_acq * 1000/128)
        length_acq_msb = 0x00FF & int(correct_length_acq/256)
        length_acq_lsb = 0x00FF & correct_length_acq
        if self.verbose:
            print("Acquisition length: ", int(correct_length_acq*1000/128), "ns.")
            # print "Arguments: ", hex(length_acq_msb), hex(length_acq_lsb)
        self.write_fpga(0xE5, length_acq_msb)  # set sEEPon MSB
        self.write_fpga(0xE6, length_acq_lsb)  # set sEEPon LSB
        return int(correct_length_acq*1000/128)

    def set_period_between_acqs(self, lEPeriod):
        repeat_length_arg = int(lEPeriod*128.0/1000) #ns
        repeat_length_msb = 0x00FF & int(repeat_length_arg/(256*256))
        repeat_length = 0x00FF & int(repeat_length_arg/256)
        repeat_length_lsb = 0x0000FF & repeat_length_arg
        print("Period between two acquisitions:", lEPeriod/1000, "us")
        # print "Arguments:", hex(repeat_length_msb), hex(repeat_length), hex(repeat_length_lsb)
        self.JSON["parameters"]["PeriodAcq"] = int(lEPeriod)
        self.JSON["parameters"]["PeriodAcq_Real"] = int(repeat_length_arg*1000/128)
        self.write_fpga(0xE7, repeat_length_msb)  # Period of one cycle MSB
        self.write_fpga(0xE8, repeat_length)  # Period of one cycle 15 to 8
        self.write_fpga(0xE9, repeat_length_lsb)  # Period of one cycle LSB
        return repeat_length_arg*1000/128

    def set_pulse_train(self, Pon, PdampOne, PHVneg, PdampTwo, pDelay, Acq):
        delays = 10
        t1 = delays
        t2 = t1 + Pon
        t3 = t2 + delays
        t4 = t3 + PdampOne
        t5 = t4 + delays
        t6 = t5 + PHVneg
        t7 = t6 + delays
        t8 = t7 + PdampTwo
        t9 = t8 + pDelay
        t10 = t9 + Acq

        self.write_fpga(0xD0, int(t1)*128/1000)
        self.write_fpga(0xD1, int(t3)*128/1000)
        self.write_fpga(0xD3, int(t5)*128/1000)  # PDamp1 and PnHV
        self.write_fpga(0xD5, int(t7)*128/1000)  # PnHV and PDamp2
        refponnhv = self.set_poff(t8)  # @unused @tocheck
        endPoff = self.set_delta_acq(t9)  # @unused @tocheck
        l_acq = self.set_length_acq(t10)
        print("----- Check of timings ---- ")
        print(t2, t4, t6, t8, t9, t10)
        print("Key timings", hex(t2*128/1000), hex(t4*128/1000), hex(t6*128/1000), hex(t8*128/1000), hex(t9*128/1000), hex(t10*128/1000))
        print("Smaller inter periods", hex(int(t1*128/1000)), hex(t3*128/1000), hex(t5*128/1000), hex(t7*128/1000))
        print("--------------------------- ")
        print("Set_pulse_train 'l_acq' " + str(l_acq))
        return l_acq


##############
#
# Processing Part
#
##############


def new_n(path, expe_id):
    os.chdir(path)
    n_max = 0
    for jsonfile in glob.glob("*.json"):
        if jsonfile.startswith(expe_id):
            N = int(jsonfile.split("-")[1].split(".")[0])
            if N > n_max:
                n_max = N
    return n_max+1


def make_clean(path):
    os.chdir(path)
    if not os.path.exists(path+"data"):
        os.makedirs(path+"data")
        print("'data' folder created")
    if not os.path.exists(path+"images"):
        os.makedirs(path+"images")
        print("'images' folder created")
    for root, dirs, files in os.walk(path):
        for filename in files:
            if filename.endswith(".json"):
                original_file = os.path.join(root, filename)
                if "data/" not in original_file:
                    print(("Moved '", original_file, " to ", "./data/"+filename))
                    os.rename(original_file, "./data/"+filename)
    return 0


def metadatag_images_batch(list_modules, exp_id, img_category, img_desc):
    """
        Used to add proper tags to all images. Dangerous to use...
    """
    if pyexivexists:
        Imgs = []
        for dirpath, dirnames, filenames in os.walk("."):
            for filename in [f for f in filenames if (f.endswith(".jpg") or f.endswith(".png"))]:
                Imgs.append(os.path.join(dirpath, filename))
        for file_name in Imgs:
            metadata = pyexiv2.ImageMetadata(file_name)
            try:
                metadata.read()
            except IOError:
                print("Not an image")
            else:
                # Modules
                metadata['Exif.Image.Software'] = list_modules  # "matty, cletus"
                metadata['Exif.Image.Make'] = exp_id  # "20180516a"
                metadata['Exif.Photo.MakerNote'] = img_category  # "oscilloscope"
                metadata['Exif.Image.ImageDescription'] = img_desc  # "Unpacking data"
                metadata.write()
            print(file_name, "done")
    else:
        print("PyExiv not present")
    return 0


def tag_image(file_name, module, experiment, category, description):
    if pyexivexists:
        metadata = pyexiv2.ImageMetadata(file_name)
        try:
            metadata.read()
        except IOError:
            print("Not an image")
        else:
            metadata['Exif.Image.Software'] = module  # "matty, cletus"
            metadata['Exif.Image.Make'] = experiment  # "20180516a"
            metadata['Exif.Photo.MakerNote'] = category  # "oscilloscope"
            metadata['Exif.Image.ImageDescription'] = description  # "Unpacking data"
            metadata.write()
    else:
        print("PyExiv not present")
    return 1


class DataToJson:
    """
        Class used to process data once acquired.
    """
    metatags = {}
    show_images = True
    IDLine = []
    TT1 = []
    TT2 = []
    tmp = []
    tdac = []
    FFT_x = []
    FFT_y = []
    EnvHil = []
    Duration = 0
    filtered_fft = []
    LengthT = 0
    Nacq = 0
    Raw = []
    Signal = []
    filtered_signal = []
    Registers = {}
    t = []
    fPiezo = 5
    Bandwidth = 1.0
    f = 0  # sampling freq
    piezo = ""
    experiment = ""
    len_acq = 0
    len_line = 0
    N = 0
    V = 0
    single = 0
    processed = False
    iD = 0
    raw_2d_image = []

    metatags["firmware_md5"] = ""

    def json_proccess(self, path):
        """
            Creates actual raw data from the signals acquired.
        """
        IDLine = []
        TT1 = []
        TT2 = []
        tmp = []

        with open(path) as json_data:
            d = json.load(json_data)
            json_data.close()

            self.description = d["experiment"]["description"]
            self.piezo = d["experiment"]["probe"]
            self.metatags["time"] = d["time"]
            self.metatags["original_json"] = d

            A = d["data"]
            for i in range(int(len(A)/2 - 1)):
                if (A[2*i+1]) < 128:
                    value = 128*(A[2*i+0] & 0b00011111) + A[2*i+1] - 4*512
                    IDLine.append(((A[2*i+0] & 0b11110000)/16 - 8)/2)  # Identify the # of the line
                    TT1.append((A[2*i+0] & 0b00001000) / 0b1000)
                    TT2.append((A[2*i+0] & 0b00010000) / 0b10000)
                    tmp.append(2.0*value/(4*512.0))
                else:
                    value = 128*(A[2*i+1] & 0b00011111) + A[2*i + 2] - 4*512
                    IDLine.append(((A[2*i+1] & 0b00011111)/16 - 8)/2)  # Identify the # of the line
                    TT1.append((A[2*i+1] & 0b00001000) / 0b1000)
                    TT2.append((A[2*i+1] & 0b00010000) / 0b10000)
                    tmp.append(2.0*value/(4*512.0))
            print("Data acquired")
            self.Registers = d["registers"]
            self.timings = d["timings"]
            self.f = float(64/(1.0+int(d["registers"]["237"])))

            t = [1.0*x/self.f + self.timings['t4']/1000.0 for x in range(len(tmp))]
            self.t = t

            for i in range(len(IDLine)):
                if IDLine[i] < 0:
                    IDLine[i] = 0
            self.LengthT = len(t)

            self.TT1 = TT1
            self.TT2 = TT2
            self.Nacq = d["timings"]["NLines"]
            self.len_acq = len(self.t)
            self.len_line = int(self.len_acq/self.Nacq)

            # Precising the DAC
            REG = [int(x) for x in list(d["registers"].keys()) if int(x) < 100]
            REG.sort()
            dac = []
            for k in REG:
                dac.append(d["registers"][str(k)])
            # Building the DAC timeline
            tdac = []
            for pts in t[0:self.len_line]:  # @todo -> corriger pour avoir une ligne de 200us
                i = int(pts/5.0)  # time in us
                try:
                    tdac.append(4.0*d["registers"][str(i+16)])
                except:
                    tdac.append(-1)

            # Updating the JSON
            self.tdac = tdac
            self.tmp = tmp
            self.single = d["registers"][str(0XEB)]
            self.t = t
            self.IDLine = IDLine
            self.metatags["firmware_md5"] = d['firmware_md5']
            self.experiment = d['experiment']
            self.parameters = d['parameters']
            self.iD = d['experiment']["id"]
            self.N = d['N']
            self.V = d['V']
            self.processed = True
            self.Duration = (self.parameters['LengthAcq']-self.parameters['DeltaAcq'])/1000.0

    def create_fft(self):
        self.FFT_x = [X*self.f/self.LengthT for X in range(self.LengthT)]
        self.FFT_y = np.fft.fft(self.tmp)
        self.filtered_fft = np.fft.fft(self.tmp)

        for k in range(int(self.LengthT/2 + 1)):
            if k < (self.LengthT * self.fPiezo * (1 - self.Bandwidth/2.0) / self.f):
                self.filtered_fft[k] = 0
                self.filtered_fft[-k] = 0
            if k > (self.LengthT * self.fPiezo *(1 + self.Bandwidth/2.0) / self.f):
                self.filtered_fft[k] = 0
                self.filtered_fft[-k] = 0

        self.filtered_signal = np.real(np.fft.ifft(self.filtered_fft))

        if self.processed:
            plt.figure(figsize=(15, 5))

            plot_time = self.FFT_x[1:self.LengthT/2]
            plot_abs_fft = np.abs(self.FFT_y[1:self.LengthT/2])
            plot_filtered_fft = np.abs(self.filtered_fft[1:self.LengthT/2])

            plt.plot(plot_time, plot_abs_fft, 'b-')
            plt.plot(plot_time, plot_filtered_fft, 'y-')

            plt.title("FFT of "+self.iD + " - acq. #: " + str(self.N))
            plt.xlabel('Freq (MHz)')
            plt.tight_layout()
            file_name = "images/"+self.iD+"-"+str(self.N)+"-fft.jpg"
            plt.savefig(file_name)
            if self.show_images:
                plt.show()
            description_experiment = "FFT of the of "+self.iD
            description_experiment += " experiment. "+self.experiment["description"]
            tag_image(file_name, "matty, cletus", self.iD, "FFT", description_experiment)

    def make_image(self):
        """
           Makes an image from the JSON content
        """
        if self.processed:  # @todo check this to get env  &  al
            fig, ax1 = plt.subplots(figsize=(20, 10))
            ax2 = ax1.twinx()
            ax2.plot(self.t[0:self.len_line], self.tdac[0:self.len_line], 'g-')
            ax1.plot(self.t[0:self.len_line], self.tmp[0:self.len_line], 'b-')
            plt.title(self.create_title_text())
            ax1.set_xlabel('Time (us)')
            ax1.set_ylabel('Signal from ADC (V)', color='b')
            ax2.set_ylabel('DAC output in mV (range 0 to 1V)', color='g')
            plt.tight_layout()
            file_name = "images/"+self.iD+"-"+str(self.N)+".jpg"
            plt.savefig(file_name)
            if self.show_images:
                plt.show()
            tag_image(file_name, "matty", self.iD, "graph", "Automated image of "+self.iD + " experiment. " + self.experiment["description"])

    @staticmethod
    def tag_image(bricks, experiment_id, img_type, img_desc, file_name):
        """
        Tags an image using available info.
        """
        # file_name = "images/"+self.iD+"-"+str(self.N)+".jpg"
        # @todo : create images folder if not exists
        if pyexivexists:
            metadata = pyexiv2.ImageMetadata(file_name)
            try:
                metadata.read()
            except IOError:
                print("Not an image")
            else:
                metadata['Exif.Image.Software'] = bricks
                metadata['Exif.Image.Make'] = experiment_id
                metadata['Exif.Photo.MakerNote'] = img_type
                metadata['Exif.Image.ImageDescription'] = img_desc
                metadata.write()
        else:
            print("pyexiv does not exist")

    def mk2DArray(self):
        """
        Creates a 2D array from raw json.
        """
        len_acquisition = len(self.tmp)
        img = []
        tmpline = []
        lineindex = 0

        for k in range(len_acquisition):
            if self.IDLine[k] != lineindex:
                img.append(tmpline)
                lineindex = self.IDLine[k]
                tmpline = []
            else:
                tmpline.append(self.tmp[k])

        duration_self = int(float(self.f)*self.Duration)

        y = [s for s in img if (len(s) > duration_self - 10 and len(s) < duration_self + 10)]
        if self.Nacq > 1:
            clean_image = np.zeros((len(y), len(self.tmp)/len(y)))
        else:
            clean_image = np.zeros((len(y), 1))

        for i in range(len(y)):
            clean_image[i][0:len(y[i])] = y[i]

        img_size = np.shape(clean_image)
        duration = (self.parameters['LengthAcq']-self.parameters['DeltaAcq'])/1000.0

        clean_image = clean_image[:, :int(duration * self.f)]
        plt.figure(figsize=(15, 10))
        if self.Nacq > 1:
            print(img_size[1], img_size[0])
            plt.imshow(np.sqrt(np.abs(clean_image)), cmap='gray', aspect=0.5*(img_size[1]/img_size[0]), interpolation='nearest')
        else:
            plt.plot(self.t[0:self.len_line], self.tmp[0:self.len_line], 'b-')

        plt.title(self.create_title_text())
        plt.tight_layout()
        file_name = "images/2DArray_" + self.iD+"-" + str(self.N) + ".jpg"
        plt.savefig(file_name)
        tag_image(file_name, "matty, " + self.piezo, self.iD, "BC", self.create_title_text().replace("\n", ". "))
        if self.show_images:
            plt.show()
        self.raw_2d_image = clean_image  # @todo: reuse this 2D image ?
        return clean_image

    def save_npz(self):
        """
           Saves the dataset as an NPZ, in the data folder.
        """
        path_npz = "data/" + self.iD + "-" + str(self.N)+".npz"  # @todo: create folder if not.
        np.savez(path_npz, self) 

    def plot_detail(self, nb_line, Start, Stop):  #@todo: use it when processing data
        """
           Shows and displays a given line, with start and stop boundaries.
        """
        # TLine = self.len_line/self.f #@unused
        Offset = nb_line * self.len_line

        plot_time_series = self.t[Offset + int(Start/self.f):Offset+int(Stop * self.f)]
        plot_signal = self.tmp[Offset+int(Start/self.f):int(Stop * self.f)]
        # @todo .. what happens if no EnvHil ?
        plot_enveloppe = self.EnvHil[Offset + int(Start/self.f):int(Stop * self.f)]

        plot_title = "Detail of "+self.iD + " - acq. #: " + str(self.N) + ", between "
        plot_title += str(Start) + " and " + str(Stop) + " (line #"+str(nb_line) + ")."

        plt.figure(figsize=(15, 5))
        plt.plot(plot_time_series, plot_signal, 'b-')
        plt.plot(plot_time_series, plot_enveloppe, 'y-')
        plt.title(plot_title)
        plt.xlabel('Time in us')
        plt.tight_layout()

        file_name = "images/detail_"+self.iD+"-"+str(self.N)+"-"
        file_name += str(Start) + "-" + str(Stop) + "-line" + str(nb_line)+".jpg"
        plt.savefig(file_name)
        if self.show_images:
            plt.show()

    def make_filtered(self, original_image):
        """
           Takes the image, then filters it around self.fPiezo .
        """
        filtered_image = []
        fft_image_filtered = []
        if len(original_image):
            num_lines, length_lines = np.shape(original_image)
            f_array = [X*self.f / length_lines for X in range(length_lines)]
            for k in range(num_lines): # number of images
                fft_single_line = np.fft.fft(original_image[k])
                fft_image_filtered.append(fft_single_line)
                for p in range(int(len(fft_single_line)/2) + 1):
                    f_min = (1000.0 * self.fPiezo * 0.7)
                    f_max = (1000.0 * self.fPiezo * 1.27)
                    if f_array[p] > f_max or f_array[p] < f_min:
                        fft_single_line[p] = 0
                        fft_single_line[-p] = 0
                filtered_image.append(np.real(np.fft.ifft(fft_single_line)))
        return filtered_image, fft_image_filtered

    def make_spectrum(self, img):
        """
           Creates a 2D array spectrum from 2D image.
        """
        spectrum = []
        if len(img):
            n_lines, len_lines = np.shape(img)
            self.FFT_x = [X*self.f / len_lines for X in range(len_lines)]   # @usuned, why?
            for k in range(n_lines):
                fft_single_line = np.fft.fft(img[k])
                spectrum.append(fft_single_line[0:n_lines/2])

            plt.figure(figsize=(15, 10))
            plt.imshow(np.sqrt(np.abs(spectrum)), extent=[0, 1000.0*self.f/2, n_lines, 0], cmap='hsv', aspect=30.0, interpolation='nearest')

            plt.axvline(x=(1000 * self.fPiezo * 1.27), linewidth=4, color='b')
            plt.axvline(x=(1000 * self.fPiezo * 0.7), linewidth=4, color='b')

            plt.xlabel("Frequency (kHz)")
            plt.ylabel("Lines #")
     
            plt.title(self.create_title_text())
            plt.tight_layout()

            file_name = "images/Spectrum_" + self.iD + "-"+str(self.N) + ".jpg"
            plt.savefig(file_name)
            img_desc = self.create_title_text().replace("\n", ". ")
            tag_image(file_name, "matty,"+self.piezo, self.iD, "FFT", img_desc)
        else:
            print("2D Array not created yet")

        return np.abs(spectrum)

    def create_title_text(self):
        """
           Creates a string to title images with appropriate acquisition details
        """
        title_text = "Experiment: " + self.iD+"-"+str(self.N)+"\nDuration: "+str(self.Duration)
        title_text += "us ("+str(self.parameters['LengthAcq'])+" - "
        title_text += str(self.parameters['DeltaAcq'])+"), for "+str(self.Nacq)
        title_text += " repeats "
        title_text += "each "+str(self.parameters['PeriodAcq_Real']/1000.0)+"us\n"
        title_text += "Fech = "+str(self.f)+"Msps, total of "+str(float(self.f)*self.Duration)
        title_text += " pts per line, Nacq = "+str(self.Nacq)+"\n"
        title_text += self.experiment["description"]+", probe: "
        title_text += self.piezo+", target = "+self.experiment["target"]+"\n"
        title_text += "Timestamp = "+str(self.metatags["time"])
        return title_text


def config_from_txt(UN0RICK, file_path):
    """
    Used with -f to get inputs from file.
    """
    ConfigText = {}
    with open(file_path) as fp:
        line = fp.readline()
        while line:
            line = line.replace("* ","").replace(": ", ":")
            line = re.sub("[\(\[].*?[\)\]]", "", line).strip()
            if len(line):
                keys = line.split(":")
                if len(keys) == 2:
                    if keys[1].isdigit():
                        ConfigText[keys[0]] = float(keys[1])
                    else:
                        ConfigText[keys[0]] = keys[1]
            line = fp.readline()

    if "bandwidthpiezo" in list(ConfigText.keys()):
        UN0RICK.Bandwidth = ConfigText["bandwidthpiezo"]
    if "fpiezo" in list(ConfigText.keys()):
        UN0RICK.fPiezo = ConfigText["fpiezo"]
    if "description" in list(ConfigText.keys()):
        UN0RICK.JSON["experiment"]["description"] = ConfigText["description"]
    if "target" in list(ConfigText.keys()):
        UN0RICK.JSON["experiment"]["target"] = ConfigText["target"]
    if "probe" in list(ConfigText.keys()):
        UN0RICK.JSON["experiment"]["probe"] = ConfigText["probe"]
    if "freq" in list(ConfigText.keys()):
        UN0RICK.set_msps(int(ConfigText["freq"]))
    if "nlines" in list(ConfigText.keys()):
        UN0RICK.set_acquisition_number_lines(int(ConfigText["nlines"]))
    if "interlinedelay" in list(ConfigText.keys()):
        ILD = ConfigText["interlinedelay"]*1000
        UN0RICK.set_period_between_acqs(int(ILD))
    if "gain" in list(ConfigText.keys()):
        g1, g2 = ConfigText["gain"].split(",")
        TGCC = UN0RICK.create_tgc_curve(int(g1), int(g2), True)[0]
        UN0RICK.set_tgc_curve(TGCC)
    if "acqtiming" in list(ConfigText.keys()):
        t1, t2 = ConfigText["acqtiming"].split(",")
        UN0RICK.set_timings(200, 100, 1000, int(t1), int(t2))

    print(ConfigText)
    UN0RICK.JSON["ConfigText"] = ConfigText
    return UN0RICK


if __name__ == "__main__":
    print("Loaded!")

    if len(sys.argv) > 1:
        if (sys.argv[1] == "-f") and (len(sys.argv) == 3) and (os.path.exists(sys.argv[2])):
            print("File exists - OK")
            UN0RICK = SpiConnector()
            UN0RICK.init()
            UN0RICK.set_multi_lines(True)
            UN0RICK.set_acquisition_number_lines(15)
            UN0RICK = config_from_txt(UN0RICK,sys.argv[2])
            UN0RICK.JSON["data"] = UN0RICK.do_acquisition()

        if "test" in sys.argv[1]:
            UN0RICK = SpiConnector()
            UN0RICK.init()
            UN0RICK.test_spi(3)

        if "single" in sys.argv[1]:
            UN0RICK = SpiConnector()
            UN0RICK.init()
            UN0RICK.test_spi(3)
            UN0RICK.set_HV(1000)
            UN0RICK.set_hilo(1)
            TGCC = UN0RICK.create_tgc_curve(600, 600, True)[0]      # Gain: linear, 10mV to 980mV
            UN0RICK.set_tgc_curve(TGCC)                             # We then apply the curve
            UN0RICK.set_tgc_constant(600)                           # Sets in mV from 0 to 1000
            UN0RICK.set_period_between_acqs(int(2500000))           # Setting 2.5ms between shots
            UN0RICK.JSON["N"] = 1                                   # Experiment ID of the day
            UN0RICK.set_multi_lines(False)                          # Single acquisition
            UN0RICK.set_acquisition_number_lines(1)                 # Setting the number of lines (1)
            UN0RICK.set_msps(0)                                     # Sampling speed setting
            A = UN0RICK.set_timings(200, 10, 200, 2000, 5000, 110000)   # Settings the series of pulses
            UN0RICK.JSON["data"] = UN0RICK.do_acquisition()         # Doing the acquisition and saves
            UN0RICK.set_led_rgb(0,0,0)

        if "multi" in sys.argv[1]:
            UN0RICK = SpiConnector()
            UN0RICK.init()
            UN0RICK.test_spi(3)
            UN0RICK.JSON["N"] = 1                                   # Experiment ID
            UN0RICK.create_tgc_curve(600, 900, False)               # Gain: expo, 300mV to 900mv
            # UN0RICK.set_tgc_curve(TGCC)                           # We then apply the curve
            UN0RICK.set_period_between_acqs(int(2500000))           # Setting 2.5ms between lines
            UN0RICK.set_multi_lines(True)                           # Multi lines acquisition
            UN0RICK.set_acquisition_number_lines(10)                # Setting the number of lines (3)
            UN0RICK.set_msps(0)                                     # Sampling speed setting
            A = UN0RICK.set_timings(200, 100, 1000, 2000, 100000)   # Settings the series of pulses
            UN0RICK.JSON["data"] = UN0RICK.do_acquisition()         # Doing the acquisition and saves

        if "process" in sys.argv[1]:
            make_clean("./")
            for MyDataFile in os.listdir("./data/"):
                if MyDataFile.endswith(".json"):
                    print(MyDataFile)
                    y = DataToJson()
                    y.show_images = False
                    y.json_proccess("./data/"+MyDataFile)
                    y.create_fft()
                    y.save_npz()
                    y.make_image()

        if "loop" in sys.argv[1]:
            UN0RICK = SpiConnector()
            UN0RICK.init()
            UN0RICK.set_multi_lines(True)                           # Multi lines acquisition
            UN0RICK.set_acquisition_number_lines(2)                 # Setting the number of lines
            UN0RICK.set_msps(3)                                     # Acquisition Freq
            A = UN0RICK.set_timings(200, 100, 2000, 5000, 200000)   # Looping on triggers
            while True:
                UN0RICK.write_fpga(0xEA, 0x01)                      # trigs
                time.sleep(50.0 / 1000.0)                           # Waits 50ms between shots
