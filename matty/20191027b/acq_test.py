from pyUn0 import *

UN0RICK = us_spi()
UN0RICK.init()
UN0RICK.test_spi(3)
UN0RICK.set_HV(500)
UN0RICK.set_hilo(1)
TGCC = UN0RICK.create_tgc_curve(100, 900, True)[0]    # Gain: linear, 10mV to 980mV
UN0RICK.set_tgc_curve(TGCC)                          # We then apply the curve
UN0RICK.set_tgc_constant(100) #sets in mV from 0 to 1000 
UN0RICK.set_period_between_acqs(int(2500000))        # Setting 2.5ms between shots
UN0RICK.JSON["N"] = 1 				 # Experiment ID of the day
UN0RICK.set_multi_lines(False)                       # Single acquisition
UN0RICK.set_acquisition_number_lines(1)              # Setting the number of lines (1)
UN0RICK.set_msps(0)                                  # Sampling speed setting
UN0RICK.JSON["experiment"]["description"] = "De.bin DAC (100) from 100 to 900, True - DAC = 400"
A = UN0RICK.set_timings(200, 100, 120, 1000, 5000, 300000)# Settings the series of pulses
UN0RICK.JSON["data"] = UN0RICK.do_acquisition()      # Doing the acquisition and saves
UN0RICK.set_ledRGB(0,0,0)
