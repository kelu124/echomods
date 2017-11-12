#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# cc-by-sa/4.0/
#
# Used in `20171112a`
#
# -------------------------

import numpy as np
import matplotlib.pyplot as plt
from scipy import signal
from scipy.interpolate import griddata
import math
from scipy.signal import decimate, convolve


#ADC1_pins = [21,22,19,15,13,11,12,10, 8]
ADC1_pins = [21,22,19,15,13,11,12,10, 8]
ADC2_pins = [38,37,36,35,33,32,26,24,23]

#ADC1_GPIO = [9, 25,10,22,27,17,18,15,14]
ADC1_GPIO =  [9 ,25,10,22,27,17,18,15,14]

ADC2_GPIO = [20,26,16,19,13,12, 7, 8,11]

ADC1len = len(ADC1_GPIO)
ADC2len = len(ADC2_GPIO)

def GetV2(Volts):
    Signal = []
    Map = np.zeros((len(Volts),ADC2len), dtype=np.int)
    for i in range(len(Volts)):
        val = int(Volts[i])
        SignalZero = 0
        for k in range(ADC2len):
            Map[i][k] = (val & 2**k)/2**k
        for k in range(ADC2len):
            SignalZero += 2**k*((val & 2**ADC2_GPIO[k])/2**ADC2_GPIO[k])
        Signal.append(SignalZero)

            
    return Signal,Map



def GetV1(Volts):
    Signal = []
    Map = np.zeros((len(Volts),ADC1len), dtype=np.int)
    for i in range(len(Volts)):
        val = int(Volts[i])
        SignalZero = 0
        for k in range(ADC1len):
            Map[i][k] = (val & 2**k)/2**k
        for k in range(ADC1len):
            SignalZero += 2**k*((val & 2**ADC1_GPIO[k])/2**ADC1_GPIO[k])
        Signal.append(SignalZero)

            
    return Signal,Map


###


def CreateUsPack(RawData):

	print RawData
	f = open(RawData, "r")
	a = np.fromfile(f, dtype=np.uint32)
	t = a[-1]
	V = a[:-1].copy()
	T = [ (( x * t ) / ( 1000.0*len(V) )) for x in 2*range(len(V))]
	Fech = 1000.0*len(V)/t # in MHz

	M = GetV2(V)[0]
	M2 = GetV1(V)[0]
	Ma = M - np.average(M[5000:7000])
	Mb = M2 - np.average(M2[5000:7000])

	rawSig = []
	for k in range(len(Ma)):
	    rawSig.append(Mb[k])
	    rawSig.append(Ma[k])


	plt.figure(figsize=(15,5))

	Interest = rawSig

	MyFFT = np.fft.fft(Interest)
	L = len(MyFFT)
	fP = L/6
	for i in range(L/2):
	    if abs(i - fP) > L/16:
		MyFFT[i] = 0
		MyFFT[-i] = 0

	plt.plot(abs(MyFFT))

	plt.title("Plots "+RawData+' .') 
	plt.savefig('Spectre_'+RawData.split("/")[-1]+'.jpg', bbox_inches='tight')
	plt.show()

	F = np.real(np.fft.ifft(MyFFT))
	FH = np.asarray(np.abs(signal.hilbert(F)))

	tableDataH = np.asarray(FH).reshape((1000,2*2500))

	plt.figure(figsize=(15,20))
	plt.imshow(np.sqrt(tableDataH))
	plt.savefig('Raw_signal_'+RawData.split("/")[-1]+'.jpg', bbox_inches='tight')
	plt.show()

	np.savez(RawData.split("/")[-1].split(".")[0]+".npz", np.int16(rawSig), np.int8(np.sqrt(tableDataH*3.0)) )

	return rawSig, np.sqrt(tableDataH*3.0)

 
## 


def CreateSC(RawImgData):

    LenLinesC = np.shape(RawImgData)[1]
    NbLinesC = np.shape(RawImgData)[0]
    SC = np.zeros((LenLinesC,LenLinesC)) + np.average(RawImgData)
    SC += 1
    maxAngle = 60.0
    step = maxAngle/(NbLinesC+1)
    CosAngle = math.cos(math.radians(maxAngle/2))
    Limit = LenLinesC*CosAngle

    points = []
    values = []

    for i in range(LenLinesC):
        for j in range(LenLinesC):
            if (  (j > LenLinesC/2 + i/(2*CosAngle)) or  (j < LenLinesC/2 - i/(2*CosAngle)) ):
                SC[i][j] = 0
                points.append([i,j])
                values.append(0)
            if (  (i > Limit) ):
                if ( (i**2 + (j-LenLinesC/2) ** 2) > LenLinesC**2):
                    SC[i][j] = 0 
                    points.append([i,j])
                    values.append(0)
    for i in range(NbLinesC):
        PointAngle = i*step-maxAngle/2
        COS = math.cos(math.radians(PointAngle))
        SIN = math.sin(math.radians(PointAngle))
        for j in range(LenLinesC):

            X = (int)( j*COS)
            Y = (int)(LenLinesC/2 - j*SIN)
            SC[X][Y] = RawImgData[i][j] 

            points.append([X,Y])
            values.append(RawImgData[i][j])

    values = np.array(values,dtype=np.int)
    
    grid_xH, grid_yH = np.mgrid[0:LenLinesC:1, 0:LenLinesC:1]
    grid_z1H = griddata(points, values, (grid_xH, grid_yH), method='linear')

    return SC,values,points,LenLinesC, grid_z1H



def CreateRawImgs (Image,FIRh):


	FIRFactor = 4
	tmp = np.transpose(Image)[0:75]
	arf = np.sum(tmp, axis=0)
	arf = decimate(arf, FIRFactor, ftype='fir')
	SeuilImg = np.min(arf[5:])+(np.average(arf[5:])-np.min(arf[5:]))/3

	Imgs = []
	GoodV = []
	for k in range(len(arf)-12):
	    if (arf[10+k]<= SeuilImg) and (arf[k+11] > SeuilImg) :
		Imgs.append( (k+FIRFactor) )
		GoodV.append((k+FIRFactor) * FIRFactor)
	


	Val = np.average(Image)
	Offset = 400
	MinTable = 10*np.min(Image)
	Zeroes = np.zeros((1000,Offset))+Val
	BigTable = []
	BigTable = np.append(Zeroes, Image[:,:3000], axis=1)
	tmp = decimate(BigTable, FIRh, ftype='fir') 

	IMGs = []
	for k in range(len(GoodV)-1):
		IMGs.append(tmp[ GoodV[k]:GoodV[k+1] ])

	return IMGs, GoodV, tmp


