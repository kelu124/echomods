# -*- coding: utf-8 -*-
"""
SPI connector class is used to create an interface FPGA board
"""

import datetime
import glob
import json
import os
import spidev
import time
from enum import Enum

try:
    import RPi.GPIO as GPIO
except ImportError:
    print("Not loading RPi.GPIO as not on RPi")
    gpioexists = False
else:
    gpioexists = True


def new_n(path, expe_id):
    os.chdir(path)
    n_max = 0
    for json_file in glob.glob("*.json"):
        if json_file.startswith(expe_id):
            N = int(json_file.split("-")[1].split(".")[0])
            if N > n_max:
                n_max = N
    return n_max + 1


class SpiRegisters(Enum):
    LED_READ = 0xC1
    LED_GREEN = 0xC2
    LED_BLUE = 0xC3
    HILO_REG = 0xD8
    MULTI_LINES_REG = 0xEB
    WRITE_REG = 0xAA
    CLEAN_MEM_POINTER = 0xEF
    ONE_SHOT = 0xEB
    SOFTWARE_TRIG = 0xEA
    HV_REG_LSB = 0xD7
    HV_REG_MSB = 0xD6
    P_OFF_MSB = 0xE1
    P_OFF_LSB = 0xE2
    ACC_SPEED_MSPS = 0xED
    NUM_LINES_LSB = 0xEE
    NUM_LINES_MSB = 0xDE
    VOLTAGE_GAIN = 0xEC
    SEEPON = 0xE0
    UNIT_P_ON_NEG = 0xD4
    UNIT_P_DAMP_INT = 0xD2
    HDA_MSB = 0xE3
    HDA_LSB = 0xE4
    LENGTH_ACQ_MSB = 0xE5
    LENGTH_ACQ_LSB = 0xE6
    REPEAT_LENGTH_MSB = 0xE7
    REPEAT_LENGTH = 0xE8
    REPEAT_LENGTH_LSB = 0xE9
    SET_PULSE_TRAIN_REG1 = 0xD0
    SET_PULSE_TRAIN_REG2 = 0xD1
    SET_PULSE_TRAIN_REG3 = 0xD3
    SET_PULSE_TRAIN_REG4 = 0xD5


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
    JSON["experiment"]["id"] = str(datetime.datetime.now().strftime("%Y%m%d")) + "a"
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
        n = int(200 / 5)
        dac_array = []
        for k in range(n + 1):
            if curve_type:
                val = int(init_value + 1.0 * k * (final_value - init_value) / n)
            else:
                val = int((final_value - init_value) * k ** 3 / n ** 3 + init_value)
            dac_array.append(val)
        dac_array[-1] = 0
        dac_array[-2] = 0
        self.set_tgc_curve(dac_array)
        return dac_array, len(dac_array)

    def set_timings(self, p_on, p_damp_one, p_HV_neg, p_off, delay_acq, acq=None):
        """
        Programs the sequence of Pon, Poff, Acquisition.
        """
        # t4 = WaitTill # 20us delay before acquisition
        # Pon, PdampOne, PHVneg, Poff, delay_acq, Acq
        # self.set_pulse_train(t1, t2, t3, t4, t5)
        self.set_pulse_train(p_on, p_damp_one, p_HV_neg, p_off, delay_acq, acq)
        # Some figures about the acquisitions now
        self.LAcq = (acq - delay_acq) / 1000  # ns to us
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

        print("NAcq = " + str(self.Nacq))
        if self.Nacq > 199999:
            raise NameError(
                "Acquisition length over 200.000 points (8Mb = Flash limit)"
            )
        return self.Nacq, self.LAcq, self.f_ech, self.number_lines

    def set_multi_lines(self, set_multi):  # OK LIT3RICK
        """
        Determines if this is a single-line of multi-line acquisition.
        """
        if set_multi:
            if self.verbose:
                print(
                    "Doing several lines."
                    "\nRemember to indicate how many lines. number_lines = 3 by default"
                )
            self.write_fpga(SpiRegisters.MULTI_LINES_REG, 1)  # Doing one line if 0, several if 1
            self.number_lines = 3
        else:
            if self.verbose:
                print("Doing a single line")
            self.write_fpga(SpiRegisters.MULTI_LINES_REG, 0)  # Doing one line if 0, several if 1
            self.number_lines = 1

    def set_tgc_curve(self, tgc_values):  # OK LIT3RICK
        """
        Sets up the TGC using an array
        """
        # Print "Setting up the DAC curves"
        if len(tgc_values) < 43:  # to correct
            for i in range(len(tgc_values)):
                if (tgc_values[i] >= 0) and (tgc_values[i] < 1020):
                    self.write_fpga(
                        16 + i, tgc_values[i] / 4
                    )  # /4 since 1024 values, on 8 bits
                else:
                    self.write_fpga(16 + i, 0)

    """
    FPGA controls.
    """

    def write_fpga(self, address, value):  # OK LIT3RICK
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
        self.write_fpga(SpiRegisters.LED_READ, red)
        self.write_fpga(SpiRegisters.LED_GREEN, gren)
        self.write_fpga(SpiRegisters.LED_BLUE, blue)

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
                print("spi maxspeed is " + str(self.spi.max_speed_hz) + "hz")
            self.set_led_rgb(0, 1, 0)
        else:
            print("Not running from a Raspberry Pi")

    """
    Testing functions
    """

    def test_spi(self, n_cycles):  # OK LIT3RICK
        """
        Blinks the HILO n_cycles times.
        """
        self.set_led_rgb(0, 0, 1)

    def set_hilo(self, hilo):  # OK LIT3RICK
        """
        Sets HILO on TGC
        """
        if hilo:
            self.write_fpga(SpiRegisters.HILO_REG, 0x01)  # 1: HILO ON
            print("HILO set HIGH")
        else:
            self.write_fpga(SpiRegisters.HILO_REG, 0x00)  # 0: HILO OFF
            print("HILO set LOW")

    def loop_spi(self):  # OK LIT3RICK
        """
        Pure debug test to spam SPI bus to have HILO LED blink continuously
        """
        while 1:
            self.write_fpga(SpiRegisters.HILO_REG, 0x01)
            self.write_fpga(SpiRegisters.HILO_REG, 0x00)

    def loop_acq(self):  # OK LIT3RICK
        """
        Pure debug test to spam SPI bus with loop acquisition.
        """
        while 1:
            self.write_fpga(SpiRegisters.MULTI_LINES_REG, 0x00)  # Doing 1 shot
            self.write_fpga(SpiRegisters.CLEAN_MEM_POINTER, 0x01)  # Cleaning memory pointer
            self.write_fpga(SpiRegisters.SOFTWARE_TRIG, 0x0)  # Software Trig : As to be clear by software
            time.sleep(0.001)  # sleep 1ms

    def clear_mem(self):  # OK LIT3RICK
        """
        Reset RAM pointer
        """
        self.write_fpga(SpiRegisters.CLEAN_MEM_POINTER, 0x01)  # To access memory

    """
    Setup functions
    """

    def set_msps(self, f_msps):
        """
        Setting acquisition speed.
        Using F, ADC speed is determined as 64Msps / (1 + f_msps)
        """
        self.write_fpga(SpiRegisters.ACC_SPEED_MSPS, f_msps)
        self.f_ech = float(64 / (1 + f_msps))
        print("Acquisition frequency set at " + str(self.f_ech) + " Msps")
        return self.f_ech

    def do_acquisition(self):
        """
        Doing an acquisition, trigs, then reads the data.
        """
        self.write_fpga(SpiRegisters.CLEAN_MEM_POINTER, 0x01)  # Cleaning memory pointer
        self.JSON["time"] = str(datetime.datetime.now())
        self.write_fpga(SpiRegisters.SOFTWARE_TRIG, 0x01)  # Software Trig : As to be clear by software
        self.JSON["data"] = []
        time.sleep(1)
        milestone = self.Nacq / 5
        start = time.time()
        if gpioexists:
            for i in range(2 * self.Nacq + 2):
                self.JSON["data"].append(self.spi.xfer([0x00])[0])
                if not ((i + 10) % milestone) and self.verbose:
                    print(
                        str((50 * i) / self.Nacq)
                        + "% - "
                        + str(self.JSON["data"][-1])
                        + " & "
                        + str(self.JSON["data"][-2])
                    )
            end = time.time()
            delta = end - start
            if self.verbose:
                print("Took %.2f seconds to transfer." % delta)
                print("for " + str(2 * self.Nacq + 2) + " transfers of data")
            self.JSON["N"] = new_n("./", self.JSON["experiment"]["id"])
            name_json = (
                self.JSON["experiment"]["id"] + "-" + str(self.JSON["N"]) + ".json"
            )
            with open(name_json, "w") as outfile:
                json.dump(self.JSON, outfile)
            self.JSON["data"] = []
            self.write_fpga(SpiRegisters.CLEAN_MEM_POINTER, 0x01)  # Cleaning memory pointer
            self.set_led_rgb(0, 0, 1)
            for i in range(2 * self.Nacq + 2):
                self.JSON["data"].append(self.spi.xfer([0x00])[0])
            name_json = (
                "_"
                + self.JSON["experiment"]["id"]
                + "-"
                + str(self.JSON["N"])
                + ".json"
            )
            with open(name_json, "w") as outfile:
                json.dump(self.JSON, outfile)
            if self.verbose:
                print(name_json + ": file saved.")
        else:
            print("Not on a RPI")
        return self.JSON["data"]

    def do_acquisition_twice(self):
        """
        Doing an acquisition, trigs, then reads the data.
        """
        self.write_fpga(SpiRegisters.CLEAN_MEM_POINTER, 0x01)  # Cleaning memory pointer
        self.JSON["time"] = str(datetime.datetime.now())
        self.write_fpga(SpiRegisters.SOFTWARE_TRIG, 0x01)  # Software Trig : As to be clear by software
        self.JSON["data"] = []
        time.sleep(1)
        milestone = self.Nacq / 5
        start = time.time()
        if gpioexists:
            for i in range(2 * self.Nacq + 2):
                self.JSON["data"].append(self.spi.xfer([0x00])[0])
            if not ((i + 10) % milestone) and self.verbose:
                print(
                    str((50 * i) / self.Nacq)
                    + "% - "
                    + str(self.JSON["data"][-1])
                    + " & "
                    + str(self.JSON["data"][-2])
                )
            end = time.time()
            delta = end - start
            if self.verbose:
                print("Took %.2f seconds to transfer." % delta)
                print("for " + str(2 * self.Nacq + 2) + " transfers of data")
            self.JSON["N"] = new_n("./", self.JSON["experiment"]["id"])
            name_json = (
                self.JSON["experiment"]["id"] + "a-" + str(self.JSON["N"]) + ".json"
            )
            with open(name_json, "w") as outfile:
                json.dump(self.JSON, outfile)
            if self.verbose:
                print(name_json + ": file saved.")
        else:
            print("Not on a RPI")

        self.write_fpga(SpiRegisters.CLEAN_MEM_POINTER, 0x01)  # Cleaning memory pointer
        self.write_fpga(SpiRegisters.LED_GREEN, 1)
        self.JSON["time"] = str(datetime.datetime.now())
        self.JSON["data"] = []
        time.sleep(1)
        milestone = self.Nacq / 5
        start = time.time()
        if gpioexists:
            for i in range(2 * self.Nacq + 2):
                self.JSON["data"].append(self.spi.xfer([0x00])[0])
            if not ((i + 10) % milestone) and self.verbose:
                print(
                    str((50 * i) / self.Nacq)
                    + "% - "
                    + str(self.JSON["data"][-1])
                    + " & "
                    + str(self.JSON["data"][-2])
                )
            end = time.time()
            delta = end - start
            if self.verbose:
                print("Took %.2f seconds to transfer." % delta)
                print("for " + str(2 * self.Nacq + 2) + " transfers of data")
            self.JSON["N"] = new_n("./", self.JSON["experiment"]["id"])
            name_json = (
                self.JSON["experiment"]["id"] + "b-" + str(self.JSON["N"]) + ".json"
            )
            with open(name_json, "w") as outfile:
                json.dump(self.JSON, outfile)
            if self.verbose:
                print(name_json + ": file saved.")
        else:
            print("Not on a RPI")
        return self.JSON["data"]

    def set_acquisition_number_lines(self, n):
        """
        Sets the number of lines to acquire.
        """
        n_msb, n_lsb = n / 256, 0x00FF & n
        self.write_fpga(SpiRegisters.NUM_LINES_LSB, n_lsb)
        self.write_fpga(SpiRegisters.NUM_LINES_MSB, n_msb)
        self.number_lines = n
        if self.verbose:
            print("Number of lines: " + str(n))

    def set_HV(self, hv_level):
        """
        Sets HV level
        """
        hv_msb, hv_lsb = hv_level / 256, 0x00FF & hv_level
        self.write_fpga(SpiRegisters.HV_REG_LSB, hv_lsb)
        self.write_fpga(SpiRegisters.HV_REG_MSB, hv_msb)
        if self.verbose:
            print("HV Level: " + str(hv_level) + " (/1Obits)")

    def config_spi(self):
        """
        Initial configuration of the FPGA.
        """
        # Setup FPGA values by default
        self.set_pon(200)  # Set PulseOn
        self.set_pulses_delays()  # Set Lengh between Pon and Poff: 100ns
        self.set_poff(2000)  # Setting Poff 2us
        # set_tgc_constant(20, spi) # gain at 20mV (2%)
        self.write_fpga(SpiRegisters.VOLTAGE_GAIN, 0x33)  # Set DAC constant
        self.set_delta_acq(7000)  # 7us
        # write_fpga(0xEA, 0x00)     # Software Trig : As to be clear by software
        self.write_fpga(SpiRegisters.MULTI_LINES_REG, 0x00)  # 0: single mode 1 continuous mode
        self.write_fpga(SpiRegisters.ACC_SPEED_MSPS, 0x03)  # Frequency of ADC acquisition
        self.set_acquisition_number_lines(0xA0)  # How many cycles in continuous mode
        print("Config FPGA done!")

    def set_tgc_constant(self, mv):
        """
        Setting TGC constant.
        """
        if mv > 1000:
            mv = 1000
        elif mv < 0:
            mv = 0
        hmv = int(mv / 4)
        print("Gain:", mv, " mV -- ", hex(hmv))
        self.write_fpga(SpiRegisters.VOLTAGE_GAIN, hmv)  # Voltage gain control: 0V to 1V

    def set_pon(self, p_on):
        if p_on > 2500:
            p_on = 2500
        elif p_on < 0:
            p_on = 0
        unit_p_on = int(p_on * 128.0 / 1000)
        self.JSON["parameters"]["Pon"] = int(p_on)
        self.JSON["parameters"]["Pon_Real"] = int(unit_p_on * 1000 / 128)
        print("POn width:", p_on, " ns -- ", hex(unit_p_on))
        self.write_fpga(SpiRegisters.SEEPON, unit_p_on)  # set sEEPon
        return unit_p_on * 1000 / 128

    def set_pon_neg(self, p_on_neg):
        if p_on_neg > 2500:
            p_on_neg = 2500
        elif p_on_neg < 0:
            p_on_neg = 0
        unit_p_on_neg = int(p_on_neg * 128.0 / 1000)
        self.JSON["parameters"]["Pon_neg"] = int(p_on_neg)
        self.JSON["parameters"]["Pon_neg_Real"] = int(unit_p_on_neg * 1000 / 128)
        print("PonNeg width:", p_on_neg, " ns -- ", hex(unit_p_on_neg))
        self.write_fpga(SpiRegisters.UNIT_P_ON_NEG, unit_p_on_neg)  # set sEEPon
        return unit_p_on_neg * 1000 / 128

    def set_p_damp_init(self, p_damp_init):
        if p_damp_init > 2500:
            p_damp_init = 2500
        elif p_damp_init < 0:
            p_damp_init = 0
        unit_p_damp_int = int(p_damp_init * 128.0 / 1000)
        self.JSON["parameters"]["Pon_neg"] = int(p_damp_init)
        self.JSON["parameters"]["Pon_neg_Real"] = int(unit_p_damp_int * 1000 / 128)
        print("PDampInt width:", p_damp_init, " ns -- ", hex(unit_p_damp_int))
        self.write_fpga(SpiRegisters.UNIT_P_DAMP_INT, unit_p_damp_int)  # set sEEPon
        return unit_p_damp_int * 1000 / 128

    @staticmethod
    def set_pulses_delays():
        p_delay = int(10 / (1000 / 128.0))
        return p_delay * 1000 / 128

    def set_poff(self, poff_value):
        # Sets the damping length.
        p_off = int(poff_value / (1000 / 128.0))
        # print sEEPoff, POff
        p_off_msb, p_off_lsb = 0x00FF & int(p_off / 256), 0x00FF & p_off
        print("Poff:", poff_value, " ns -- ", hex(p_off_msb), hex(p_off_lsb))
        self.JSON["parameters"]["Poff"] = int(poff_value)
        self.JSON["parameters"]["Poff_Real"] = int(p_off * 1000 / 128)
        self.write_fpga(SpiRegisters.P_OFF_MSB, p_off_msb)  # set sEEPon MSB
        self.write_fpga(SpiRegisters.P_OFF_LSB, p_off_lsb)  # set sEEPon LSB
        return p_off * 1000 / 128

    def set_delta_acq(self, acquisition_delay_val):
        """
        Setting Poff to Acq delay sEEDelayACQ
        """
        if acquisition_delay_val > 255 * 255:
            acquisition_delay_val = 254 * 254
        elif acquisition_delay_val < 0:
            acquisition_delay_val = 0
        hda = int((128 * acquisition_delay_val) / 1000.0)
        hda_msb, hda_lsb = int(hda / 256), 0x00FF & hda
        print("Delay between:", hda * 1000 / 128, "ns -- ", hex(hda_msb), hex(hda_lsb))
        self.JSON["parameters"]["DeltaAcq"] = int(acquisition_delay_val)
        self.JSON["parameters"]["DeltaAcq_Real"] = int(hda * 1000 / 128)
        self.write_fpga(SpiRegisters.HDA_MSB, hda_msb)  # set sEEPon MSB
        self.write_fpga(SpiRegisters.HDA_LSB, hda_lsb)  # set sEEPon LSB
        return acquisition_delay_val

    def set_length_acq(self, LAcqI):
        correct_length_acq = int((128 * LAcqI) / 1000)  # (LAcqI*128/1000)
        # print correct_length_acq, hex(LAcq), hex(LAcqI)
        self.JSON["parameters"]["LengthAcq"] = int(LAcqI)
        self.JSON["parameters"]["LengthAcq_Real"] = int(correct_length_acq * 1000 / 128)
        length_acq_msb = 0x00FF & int(correct_length_acq / 256)
        length_acq_lsb = 0x00FF & correct_length_acq
        if self.verbose:
            print("Acquisition length: ", int(correct_length_acq * 1000 / 128), "ns.")
            # print "Arguments: ", hex(length_acq_msb), hex(length_acq_lsb)
        self.write_fpga(SpiRegisters.LENGTH_ACQ_MSB, length_acq_msb)  # set sEEPon MSB
        self.write_fpga(SpiRegisters.LENGTH_ACQ_LSB, length_acq_lsb)  # set sEEPon LSB
        return int(correct_length_acq * 1000 / 128)

    def set_period_between_acqs(self, le_period):
        repeat_length_arg = int(le_period * 128.0 / 1000)  # ns
        repeat_length_msb = 0x00FF & int(repeat_length_arg / (256 * 256))
        repeat_length = 0x00FF & int(repeat_length_arg / 256)
        repeat_length_lsb = 0x0000FF & repeat_length_arg
        print("Period between two acquisitions:", le_period / 1000, "us")
        # print "Arguments:", hex(repeat_length_msb), hex(repeat_length), hex(repeat_length_lsb)
        self.JSON["parameters"]["PeriodAcq"] = int(le_period)
        self.JSON["parameters"]["PeriodAcq_Real"] = int(repeat_length_arg * 1000 / 128)
        self.write_fpga(SpiRegisters.REPEAT_LENGTH_MSB, repeat_length_msb)  # Period of one cycle MSB
        self.write_fpga(SpiRegisters.REPEAT_LENGTH, repeat_length)  # Period of one cycle 15 to 8
        self.write_fpga(SpiRegisters.REPEAT_LENGTH_LSB, repeat_length_lsb)  # Period of one cycle LSB
        return repeat_length_arg * 1000 / 128

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

        self.write_fpga(SpiRegisters.SET_PULSE_TRAIN_REG1, int(t1) * 128 / 1000)
        self.write_fpga(SpiRegisters.SET_PULSE_TRAIN_REG2, int(t3) * 128 / 1000)
        self.write_fpga(SpiRegisters.SET_PULSE_TRAIN_REG3, int(t5) * 128 / 1000)  # PDamp1 and PnHV
        self.write_fpga(SpiRegisters.SET_PULSE_TRAIN_REG4, int(t7) * 128 / 1000)  # PnHV and PDamp2
        refponnhv = self.set_poff(t8)  # @unused @tocheck
        endPoff = self.set_delta_acq(t9)  # @unused @tocheck
        l_acq = self.set_length_acq(t10)
        print("----- Check of timings ---- ")
        print(t2, t4, t6, t8, t9, t10)
        print(
            "Key timings",
            hex(t2 * 128 / 1000),
            hex(t4 * 128 / 1000),
            hex(t6 * 128 / 1000),
            hex(t8 * 128 / 1000),
            hex(t9 * 128 / 1000),
            hex(t10 * 128 / 1000),
        )
        print(
            "Smaller inter periods",
            hex(int(t1 * 128 / 1000)),
            hex(t3 * 128 / 1000),
            hex(t5 * 128 / 1000),
            hex(t7 * 128 / 1000),
        )
        print("--------------------------- ")
        print("Set_pulse_train 'l_acq' " + str(l_acq))
        return l_acq
