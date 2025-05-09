#!/usr/bin/python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# GPLv3
# -------------------------

'''Description: Library for the un0rick platform.'''

__author__      = "kelu124"
__copyright__   = "Copyright 2016, Kelu124"
__license__ = "GPLv3"

'''
Used inter alia in `WIP`
'''

import spidev
import matplotlib
import matplotlib.pyplot as plt
import json
import time
import datetime
from scipy import signal
from scipy.interpolate import griddata
import math
from scipy.signal import decimate, convolve
import json 
import re
import glob, os
import sys
import numpy as np


try:
	import RPi.GPIO as GPIO
except:
	print "Not loading RPi.GPIO as not on RPi"
try:
	import pyexiv2
except:
	print "pyexiv2 does not exist on RPi"

##############
#
# RPI Part
#
##############

#----------------
# DAC Control
#----------------
class us_spi:

	JSON = {}
	spi = spidev.SpiDev()

	JSON["firmware_md5"]="fa6a7560ade6d6b1149b6e78e0de051f"
	JSON["firmware_version"]="e_un0"
	JSON["data"]=[]
	JSON["time"] = unicode(datetime.datetime.now())
	JSON["registers"]={}
	JSON["experiment"]={}
	JSON["parameters"]={}
	JSON["timings"]={}
	JSON["experiment"]["id"] = "na"
	JSON["experiment"]["description"]="na"
	JSON["experiment"]["probe"]="na"
	JSON["experiment"]["target"] = "na"
	JSON["experiment"]["position"] = "na"
	JSON["V"]="-1"

	Fech = 0
	Nacq = 0
	LAcq = 0
	NLines = 0

	def updateACQTIme(self):
	    # to update the number of acquisitions to do, when one parameter changes
	    self.Nacq = int(self.LAcq * self.Fech * self.NLines)
	    return self.Nacq

	def CreateDACCurve(self,Deb,Fin,CurveType):
	    n = 200/5
	    DACValues = []
	    for k in range(n+1):
		if CurveType:
		    val = int(Deb+1.0*k*(Fin-Deb)/n)
		    print "Curvetype is set to linear" 
		else:
		    val = int((Fin-Deb)*k**3/n**3+Deb)
		    print "Curvetype is set to cubic" 
		DACValues.append(val) 
	    DACValues[-1] = 0
	    DACValues[-2] = 0
	    self.setDACCurve(DACValues)
	    return DACValues,len(DACValues)

	def setTimings(self,t1,t2,t3,WaitTill,t5):
	    t4 = WaitTill # 20us delay before acquisition
	    self.setPulseTrain(t1,t2,t3,t4,t5)
	    # Some figures about the acquisitions now
	    self.LAcq = (t5-WaitTill)/1000 #ns to us 
	    self.updateACQTIme()
	    self.JSON["timings"]["t1"]     = t1
	    self.JSON["timings"]["t2"]     = t2
	    self.JSON["timings"]["t3"]     = t3
	    self.JSON["timings"]["t4"]     = WaitTill
	    self.JSON["timings"]["t5"]     = t5
	    self.JSON["timings"]["NAcq"]   = self.Nacq
	    self.JSON["timings"]["LAcq"]   = self.LAcq
	    self.JSON["timings"]["Fech"]   = self.Fech
	    self.JSON["timings"]["NLines"] = self.NLines	 
	    print "NAcq = "+str(self.Nacq)
	    if self.Nacq > 499999:
	        raise NameError('Acquisition length over 500.000 points (8Mb = Hardware Flash limit)')
	    return self.Nacq, self.LAcq, self.Fech, self.NLines	   
 
	def setMultiLines(self,Bool):
	    if Bool:
		print "Remember to indicate how many lines"
		self.WriteFPGA(0xEB,1) # Doing one line if 0, several if 1
		self.Nacq = 0
	    else:
		print "Doing a single line"
		self.WriteFPGA(0xEB,0) # Doing one line if 0, several if 1
		self.Nacq = 1
		
	def setDACCurve(self,DACValues):
	    print "Setting up the DAC" 
	    if len(DACValues) < 43: # to correct
		for i in range(len(DACValues)):
		    if (DACValues[i] >= 0) and (DACValues[i] < 1020):
		        self.WriteFPGA(16+i,DACValues[i]/4)
		    else:
		        self.WriteFPGA(16+i,0)
		    #print 16+i,len(DACValues)

	#----------------
	# FPGA Controls
	#----------------

	def WriteFPGA(self,adress,value):
	    self.spi.xfer([0xAA] )
	    self.spi.xfer([adress] )
	    self.spi.xfer([value] )
	    self.JSON["registers"][int(adress)]=value

	    
	def init(self):
	    GPIO.setmode(GPIO.BCM)
	    PRESET = 23 ## Reset for the FPGA
	    IO4 = 26 ## 26 is the output connected to 
	    
	    CS_FLASH = 7
	    GPIO.setup(CS_FLASH,GPIO.OUT)  
	    GPIO.output(CS_FLASH,GPIO.LOW)

	    GPIO.setup(PRESET,GPIO.OUT)
	    GPIO.setup(IO4,GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
	    print "Reset GPIO 23 - Low 1s"
	    GPIO.output(PRESET,GPIO.LOW)
	    time.sleep(3)
	    print "Reset GPIO 23 - High 0.2s"
	    GPIO.output(PRESET,GPIO.HIGH)
	    time.sleep(0.2)
	    self.spi.open(0,0) # CS2 - FPGA, on CE1 = IO4
	    self.spi.mode = 0b01
	    print "spi.cshigh is " + str(self.spi.cshigh)
	    print "spi mode is " + str(self.spi.mode)
	    self.spi.max_speed_hz = 2000000
	    print "spi maxspeed is "+str(self.spi.max_speed_hz)+"hz" 

	#----------------
	# Testing functions
	#----------------

	def TestSPI(self,ncycles):
	    i = 0
	    while i < ncycles:
		self.WriteFPGA(0xEB,0x01) # 0: single mode 1 continious mode
		time.sleep(0.5)
		self.WriteFPGA(0xEB,0x00) # 0: single mode 1 continious mode
		time.sleep(0.5)  
		i = i+1

	def LoopSPI(self):
	    while 1:
		self.WriteFPGA(0xEB,0x01) # 0: single mode 1 continious mode
		self.WriteFPGA(0xEB,0x00) # 0: single mode 1 continious mode


	def LoopAcq(self):
	    while 1:
		self.WriteFPGA(0xEB,0x00) # Doing 1 shot 
		self.WriteFPGA(0xEF,0x01) # Cleaning memory pointer
		self.WriteFPGA(0xEA,0x0) # Software Trig : As to be clear by software
		time.sleep(0.001) # sleep 1ms


	def ClearMem(self):
	    self.WriteFPGA(0xEF,0x01) # To access memory
        
	#----------------
	# Setup functions
	#----------------
	def setMsps(self,F):
	    self.WriteFPGA(0xED,F)
	    self.Fech = float(64/((1+F)))
	    self.updateACQTIme()
	    print "Acquisition frequency set at "+str(self.Fech)+" Msps"
	    return self.Fech

	def doAcquisition(self):
	    self.WriteFPGA(0xEF,0x01) # Cleaning memory pointer
	    self.JSON["time"] = unicode(datetime.datetime.now())
	    self.WriteFPGA(0xEA,0x01) # Software Trig : As to be clear by software
	    self.JSON["data"] = []
	    milestone = self.Nacq / 5
	    start = time.time()
	    for i in range(2*self.Nacq+2):
	        self.JSON["data"].append ( self.spi.xfer([0x00] )[0] )
	        if not (i%milestone):
	            print str((50*i)/self.Nacq)+"%"
	    end = time.time()
	    delta = end - start
	    print "Took %.2f seconds to transfer." % delta 
	    print "for "+str(2*self.Nacq+2)+" transfers of data"
	    JSONName = self.JSON["experiment"]["id"]+"-"+str(self.JSON["N"])+".json"
	    with open(JSONName, 'w') as outfile:
	        json.dump(self.JSON, outfile)
	    print JSONName+": file saved."
	    return self.JSON["data"]

	def setNLines(self,n):
	    if n > 0 and n < 255:
		    self.setMultiLines(True) # doing several lines
		    self.WriteFPGA(0xEE,n)
		    self.NLines = n
		    self.updateACQTIme()
	    else:
		    raise NameError('NLines must be between 0 and 255')
	    print "Number of lines set to: "+str(n)
	    return n

	def configSPI(self):
	    # Setup FPGA values by default
	    self.setPon(200)          # Set PulseOn: by default 200ns
	    self.setPulsesDelay(100)  # Set Lengh between Pon and Poff: 100ns
	    self.setPoff(2000)        # Setting Poff (damper) 2us 
	    self.WriteFPGA(0xEC,0x33) # Set DAC constant
	    self.setDeltaAcq(7000)    # Let's wait 7us before starting the acquisition 
	    self.WriteFPGA(0xEB,0x00) # 0: single mode 1 continious mode
	    self.WriteFPGA(0xED,0x03) # Frequency of ADC acquisition / sEEADC_freq (3 = 16Msps, 1 = 32, 0 = 64, 2 = 21Msps)
	    self.SetNLines(0xA0)      # How many cycles in countinious mode
	    print "Default config of FPGA done."

	def setDACConstant(self,mV):
	    if mV > 1000:
		mV = 1000
	    elif mV < 0:
		mV = 0   
	    hmV = mV/4
	    print "Gain:", mV," mV -- ",hex(hmV)
	    self.WriteFPGA(0xEC,hmV) # Voltage gain control: 0V to 1V


	def setPon(self,POn):
	    if POn > 2500:
		POn = 2500
	    elif POn < 0:
		POn = 0
	    HPon = int((1.28*POn)/10) 
	    self.JSON["parameters"]["Pon"] = int(POn)
	    self.JSON["parameters"]["Pon_Real"] = int(HPon)
	    print "Pulse width:", POn," ns -- ",hex(HPon)
	    self.WriteFPGA(0xE0,HPon) # set sEEPon
	    return HPon*10
	    
	def setPulsesDelay(self,DeltaPP):
	# Set Lengh between Pon and Poff
	    if DeltaPP > 2500:
		DeltaPP = 2500
	    elif DeltaPP < 0:
		DeltaPP = 0
	    HPP =int((1.28*DeltaPP)/10) 
	    #print  hex(HPP)
	    self.JSON["parameters"]["PulsesDelay"] = int(DeltaPP)
	    self.JSON["parameters"]["PulsesDelay_Real"] = int(HPP)
	    print "Pulses delay:", DeltaPP," ns -- ",hex(HPP)
	    self.WriteFPGA(0xD0,HPP) # set sEEPon
	    return HPP*10

	def setPoff(self,sEEPoff):
	    # Sets the damping length.
	    POff = int((1.28*sEEPoff)/10) 
	    #print sEEPoff,POff
	    POffMSB, POffLSB = 0x00FF&POff/256,0x00FF&POff 
	    print "Poff:", sEEPoff," ns -- ",hex(POffMSB),hex(POffLSB)
	    self.JSON["parameters"]["Poff"] = int(sEEPoff)
	    self.JSON["parameters"]["Poff_Real"] = int(POff)
	    self.WriteFPGA(0xE1,POffMSB) # set sEEPon MSB
	    self.WriteFPGA(0xE2,POffLSB) # set sEEPon LSB
	    return POff*10

	    # Setting Poff to Acq delay sEEDelayACQ
	def setDeltaAcq(self,DeltaAcq):
	    if DeltaAcq > 255*255:
		DeltaAcq = 254*254
	    elif DeltaAcq < 0:
		DeltaAcq = 0

	    hDA = int((1.28*DeltaAcq)/10)
	    hDAMSB, hDALSB = hDA/256 , 0x00FF&hDA 
	    print "Delay between:",hDA*1000/128,"ns -- ", hex(hDAMSB),hex(hDALSB)
	    self.JSON["parameters"]["DeltaAcq"] = int(DeltaAcq)
	    self.JSON["parameters"]["DeltaAcq_Real"] = int(hDA)
	    self.WriteFPGA(0xE3,hDAMSB) # set sEEPon MSB
	    self.WriteFPGA(0xE4,hDALSB) # set sEEPon LSB
	    return DeltaAcq

	def SetLengthAcq(self,LAcqI):
	    LAcqCorrected = int((128*LAcqI)/1000) # (LAcqI*128/1000)
	    #print LAcqCorrected,hex(LAcq),hex(LAcqI)
	    self.JSON["parameters"]["LengthAcq"] = int(LAcqI)
	    self.JSON["parameters"]["LengthAcq_Real"] = int(LAcqCorrected)
	    LAcqMSB, LAcqLSB = 0x00FF&LAcqCorrected/256 , 0x00FF&LAcqCorrected
	    print "Acquisition length: ", int(LAcqCorrected*1000/128), "ns -- ",hex(LAcqMSB),hex(LAcqLSB)
	    self.WriteFPGA(0xE5,LAcqMSB) # set sEEPon MSB
	    self.WriteFPGA(0xE6,LAcqLSB) # set sEEPon LSB
	    return int(LAcqCorrected*1000/128)

	def setPeriodAcq(self,lEPeriod):
	    lEPNs = int((1.28*lEPeriod)/10) #ns
	    EPNsMSB, EPNs, EPNsLSB = 0x00FF&lEPNs/(256*256),0x00FF&lEPNs/256,0x0000FF&lEPNs 
	    print "Period between two acquisitions:", lEPeriod,"us --", hex(EPNsMSB),hex(EPNs),hex(EPNsLSB) 
	    self.JSON["parameters"]["PeriodAcq"] = int(lEPeriod)
	    self.JSON["parameters"]["PeriodAcq_Real"] = int(lEPNs)
	    self.WriteFPGA(0xE7,EPNsMSB) # Period of one cycle MSB
	    self.WriteFPGA(0xE8,EPNs) # Period of one cycle 15 to 8
	    self.WriteFPGA(0xE9,EPNsLSB) # Period of one cycle LSB
	    return lEPNs*10

	def setPulseTrain(self,Pon,Pdelay,Poff,DelayAcq,Acq):
	    RPon = self.setPon(Pon)
	    RPD = self.setPulsesDelay(RPon+Pdelay)
	    RPOff = self.setPoff(Poff+RPD)
	    RDAcq = self.setDeltaAcq(DelayAcq)
	    LenAcq = self.SetLengthAcq(Acq)
	    self.updateACQTIme()
	    print "setPulseTrain Lacq "+str(LenAcq)
	    return LenAcq


##############
#
# Processing Part
#
##############

def MetaDataImg(Modules,Experiment,Category,Description):
    Imgs = []
    for dirpath, dirnames, filenames in os.walk("."):
        for filename in [f for f in filenames if ( f.endswith(".jpg") or f.endswith(".png") )]:
            Imgs.append( os.path.join(dirpath, filename) )

    for FileName in Imgs:
        edit = 0

        metadata = pyexiv2.ImageMetadata(FileName)
        try:
            metadata.read()
        except IOError:
            print "Not an image"
        else:
            # Modules
            metadata['Exif.Image.Software'] = Modules # "matty,cletus"
            metadata['Exif.Image.Make'] = Experiment #"20180516a"
            metadata['Exif.Photo.MakerNote'] = Category #"oscilloscope"
            metadata['Exif.Image.ImageDescription'] = Description #"Unpacking data"
            metadata.write()
            
        print FileName, "done"

def TagImage(FileName,Modules,Experiment,Category,Description):

        metadata = pyexiv2.ImageMetadata(FileName)
        try:
            metadata.read()
        except IOError:
            print "Not an image"
        else:
            metadata['Exif.Image.Software'] = Modules # "matty,cletus"
            metadata['Exif.Image.Make'] = Experiment #"20180516a"
            metadata['Exif.Photo.MakerNote'] = Category #"oscilloscope"
            metadata['Exif.Image.ImageDescription'] = Description #"Unpacking data"
            metadata.write()
	return 1

class us_json:
    
    IDLine = []
    TT1 = []
    TT2 = []
    tmp = [] 
    tdac = [] 
    FFT_x = [] 
    FFT_y = []
    EnvHil= []
    FFT_filtered = []
    LengthT = 0
    Nacq = 0
    Raw = [] 
    Signal = []
    SignalFiltered = []
    Registers = {}
    t= []
    fPiezo = 3.5
    f = 0 # sampling freq
    firmware_md5 = ""
    experiment = ""
    len_acq = 0
    len_line= 0
    N = 0
    V = 0
    single = 0
    processed = False
    iD =  0
    
    def JSONprocessing(self,path):
        #print("This is a message inside the class.")
        IDLine = []
        TT1 = []
        TT2 = []
        tmp = [] 
        tdac = [] 
        with open(path) as json_data:
            DATA = {}
            d = json.load(json_data)
            json_data.close()
            
            self.description = d["experiment"]["description"]
            self.piezo = d["experiment"]["probe"]

            A = d["data"] 
            #print d.keys()
            for i in range(len(A)/2-1):
                if (A[2*i+1]) < 128:
                #print "first"
                    value = 128*(A[2*i+0]&0b0000111) + A[2*i+1] - 512
                    IDLine.append(((A[2*i+0]&0b11110000)/16  -8 ) /2 ) # Identify the # of the line
                    TT1.append( (A[2*i+0] & 0b00001000) / 0b1000)
                    TT2.append( (A[2*i+0] & 0b00010000) / 0b10000)
                    tmp.append( 2.0*value/512.0 ) 
                else:
                #print "second"
                    value = 128*(A[2*i+1]&0b111) + A[2*i+2] - 512
                    IDLine.append(((A[2*i+1]&0b11110000)/16 -8) /2 ) # Identify the # of the line
                    TT1.append( (A[2*i+1] & 0b00001000) / 0b1000)
                    TT2.append( (A[2*i+1] & 0b00010000) / 0b10000)
                    tmp.append( 2.0*value/512.0 )
            print "Data acquired"
            self.f = float(64/((1.0+int( d["registers"]["237"] ) )))
            t = [ 1.0*x/self.f  for x in range(len(tmp))]
            self.t = t
            for i in range(len(IDLine)):
                if IDLine[i] < 0:
                    IDLine[i] = 0
            self.LengthT = len(t)
            
            #self.EnvHil = self.SignalFiltered
            #self.EnvHil = np.asarray(np.abs(signal.rrt(self.SignalFiltered)))

            self.TT1 = TT1
            self.TT2 = TT2
            self.Nacq = d["timings"]["NLines"]
            self.len_acq = len(self.t)
            self.len_line = self.len_acq#/self.Nacq
            self.Registers = d["registers"]
            self.timings = d["timings"]

            # Precising the DAC
            REG = [int(x) for x in d["registers"].keys() if int(x) < 100]
            REG.sort() 
            dac = []
            for k in REG:
                dac.append(d["registers"][str(k)])
            # Building the DAC timeline
            tdac = []
            for pts in t[0:self.len_line]:
                i = int(pts/5.0) # time in us
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
            self.firmware_md5 = d['firmware_md5']
            self.experiment = d['experiment']
            self.parameters = d['parameters']
            self.iD = d['experiment']["id"]
            self.N = d['N']
            self.V = d['V']
            self.processed = True
            
            
    def mkFFT(self):
	if 1:
		self.FFT_x = [ X*self.f / (self.LengthT) for X in range(self.LengthT)] 
		self.FFT_y = np.fft.fft(self.tmp)
		self.FFT_filtered = np.fft.fft(self.tmp)

		for k in range (self.LengthT/2 + 1):
		    if k < (self.LengthT * self.fPiezo * 0.5 / self.f):
		        self.FFT_filtered[k] = 0
		        self.FFT_filtered[-k] = 0
		    if k > (self.LengthT * self.fPiezo *1.5 / self.f):
		        self.FFT_filtered[k] = 0
		        self.FFT_filtered[-k] = 0
		    
		self.SignalFiltered = np.real(np.fft.ifft(self.FFT_filtered))

        if self.processed:
            plt.figure(figsize=(15,5))
            plt.plot(self.FFT_x[1:self.LengthT/2], np.abs(self.FFT_y[1:self.LengthT/2]), 'b-') 
            plt.plot(self.FFT_x[1:self.LengthT/2], np.abs(self.FFT_filtered[1:self.LengthT/2]), 'y-') 
            plt.title( "FFT of "+self.iD + " - acq. #: "+ str(self.N))
            plt.xlabel('Freq (MHz)') 
            plt.tight_layout()
            FileName = "images/"+self.iD+"-"+str(self.N)+"-fft.jpg"
            plt.savefig(FileName)
            plt.show() 
            self.TagImage("matty,cletus",self.iD,"FFT","FFT of the of "+self.iD +" experiment. "+self.experiment["description"])

            
            
    def mkImg(self):
        if self.processed:
            fig, ax1 = plt.subplots(figsize=(20,10))
            ax2 = ax1.twinx() 
            ax2.plot(self.t[0:self.len_line], self.tdac[0:self.len_line], 'g-')
            ax1.plot(self.t[0:self.len_line], self.tmp[0:self.len_line], 'b-')
            plt.title( self.iD + " - acq. #: "+ str(self.N))
            ax1.set_xlabel('Time (us)')
            ax1.set_ylabel('Signal from ADC (V)', color='b')
            ax2.set_ylabel('DAC output in mV (range 0 to 1V)', color='g')
            plt.tight_layout()
            FileName = "images/"+self.iD+"-"+str(self.N)+".jpg"
            plt.savefig(FileName)
            plt.show() 
            self.TagImage("matty,cletus",self.iD,"graph","Graph of "+self.iD +" experiment. "+self.experiment["description"])

    def TagImage(self,Module,ID,Type,Description):
            ## Updating Metadata
            FileName = "images/"+self.iD+"-"+str(self.N)+".jpg"
            metadata = pyexiv2.ImageMetadata(FileName)
            try:
                metadata.read()
            except IOError:
                print "Not an image"
            else: 
                metadata['Exif.Image.Software'] = Module
                metadata['Exif.Image.Make'] = ID
                metadata['Exif.Photo.MakerNote'] = Type 
                metadata['Exif.Image.ImageDescription'] = Description 
                metadata.write()
    
                
    def SaveNPZ(self):
        NPZPath = "data/"+self.iD+"-"+str(self.N)+".npz"
        np.savez(NPZPath, self)
        #print "Saved at "+NPZPath

    def PlotDetail(self,NbLine,Start,Stop):

	TLine = self.len_line/self.f
	Offset = NbLine*self.len_line

	plt.figure(figsize=(15,5))
	plt.plot(self.t[Offset+int(self.len_line*Start/TLine):Offset+int(self.len_line*Stop/TLine)], self.tmp[Offset+int(self.len_line*Start/TLine):int(self.len_line*Stop/TLine)], 'b-') 
	plt.plot(self.t[Offset+int(self.len_line*Start/TLine):Offset+int(self.len_line*Stop/TLine)], self.EnvHil[Offset+int(self.len_line*Start/TLine):int(self.len_line*Stop/TLine)], 'y-') 

	plt.title( "Detail of "+self.iD + " - acq. #: "+ str(self.N)+", between "+str(Start)+" and "+str(Stop)+" (line #"+str(NbLine)+").")
	plt.xlabel('Time in us') 
	plt.tight_layout()
        FileName = "images/detail_"+self.iD+"-"+str(self.N)+"-"+str(Start)+"-"+str(Stop)+"-line"+str(NbLine)+".jpg"
        plt.savefig(FileName)
	plt.show() 


##############
#
# Main
#
##############

if __name__ == "__main__":
	print "Loaded!"
