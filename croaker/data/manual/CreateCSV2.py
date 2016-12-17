#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# cc-by-sa/4.0/
# -------------------------

'''Description: Creating the CVS from a log file.'''

__author__      = "kelu124"
__copyright__   = "Copyright 2016, Kelu124"
__license__ 	= "cc-by-sa/4.0/"

import sys
import numpy as np
from numpy.fft import fft2, ifft2, fft, ifft
from operator import itemgetter, attrgetter
import Image
from math import *
import math
import os.path, time
import datetime
# Prend en argument un fichier Signal-bitscope-DATA.log

try:
    sys.argv[1]
except NameError:
    startingpoint = 'Missing an arg'
else:
    startingpoint = sys.argv[1]

 
print startingpoint

k = 0

itsdate = datetime.datetime.fromtimestamp(os.path.getmtime(startingpoint)) 
filename = itsdate.strftime('%Y%m%d-%H%M%S')

#print "last modified: %s" % itsdate
#print "last modified: %s" % filename
#print "created: %s" % time.ctime(os.path.getctime(startingpoint))


  
Tableau=[]
LigneRef=[]
descriptionFile=""
# Opening actual data
with open(startingpoint, 'r') as echOpenLog:
	for line in echOpenLog:
	    if (("Connected" not in line) and ("#description" not in line)):
		k=k+1
		line = line.split(';')
		del line[-1]
		Tableau.append(line)
	    if ("#description" in line):
		descriptionFile = line

SortedTable = Tableau

PointsPerLine = len(SortedTable[0])
NbOfLines = len(SortedTable)
print PointsPerLine
print NbOfLines

SortedTable = np.array(SortedTable).astype(float)



# Opening actual data
with open("baseline", 'r') as echOpenLog:
	for line in echOpenLog:
	    if ("Connected" not in line):
		k=k+1
		line = line.split(';')
		del line[-1]
		LigneRef.append(line)

PointsPerLineRef = len(LigneRef[0])
NbOfLinesRef = len(LigneRef)

# Removing the reference
Baseline=np.zeros(shape=(PointsPerLine))

AverageNumber = 10
for i in range(10):
    for j in range(PointsPerLine):
	Baseline[j] +=  int(Tableau[i][j])

#del Baseline[0]
#del Baseline[0]
Baseline = Baseline/AverageNumber
 
numFullImages = 0
for i in range(NbOfLines):
    for j in range(PointsPerLine):
	if (j>1):
	    SortedTable[i][j] = abs(SortedTable[i][j] - 0.9*Baseline[j]) 
	elif (j==0):
	    numImages = SortedTable[i][j] + 1
	    if (numImages>numFullImages):
		numFullImages = numImages

numFullImages = int(numFullImages - 1)

print  numFullImages

# Creation de l'image
NbSamples = 0
MeanZone = 0
MaxSignal = 0.0001

# On normalise les donnees
SortedTable = np.array(SortedTable).astype(int)
 
for i in range(NbOfLines):
    for j in range(PointsPerLine):
	if (j>16 and j<30):
	    MeanZone += SortedTable[i][j]
	    NbSamples += 1
	if (j>42):
	    if (SortedTable[i][j]>MaxSignal):
		MaxSignal = SortedTable[i][j]

MeanZone = MeanZone/NbSamples
SortedTable = abs(SortedTable - MeanZone) # Removing all information
SortedTable = np.array(SortedTable).astype(float)


# On normalise les donnees
MaxSignal = MaxSignal/1.56 # To get interesting signals from there

for i in range(NbOfLines):
    for j in range(PointsPerLine):
	if (j>1):
	    SortedTable[i][j] = (SortedTable[i][j]*16383.0/MaxSignal)

SortedTable = np.array(SortedTable).astype(int)

size = (NbOfLines,PointsPerLine) # aller jusqu'au bocal
ImagePoints=np.zeros(shape=(NbOfLines,PointsPerLine))

# On recontrsuit l'image pour la sauver
sizeImg = (61,PointsPerLine) # aller jusqu'au bocal

print SortedTable

for eachImage in range(numFullImages):
	print eachImage
	im = Image.new('RGB',sizeImg)
	pix = im.load()


	# Creation d'un fichier donnees
	st = filename+"-"+str(eachImage)+".csv"
	targetFile = open(st, 'w')

	#Boucles
	for i in range(61): # les lignes
	    for j in range(PointsPerLine-2):
		pix[i,j] = 128
		value = SortedTable[eachImage*60+i][j+2]
		tmp = (int)(value/64)
		pix[i,j] = (tmp,tmp,tmp)
		if(j==(size[1]-1)):
			targetFile.write(str(value))
		else:
			targetFile.write(str(value)+";")
	    targetFile.write("\n")

	targetFile.write("# More details:\n")
	targetFile.write("#timestamp:"+str(filename)+"\n")
	targetFile.write("#originalfilename:"+str(startingpoint)+"\n")
	if (len(descriptionFile)):
	    targetFile.write(descriptionFile)
	    print "--> "+descriptionFile
	else:
	    print "Pas de description"
	targetFile.write("#lines:60\n")
	targetFile.write("#length:"+str(size[1]-2)+"\n")
	targetFile.write("#frequency:unknown-feather\n")
	targetFile.write("#piezofrequency:3500000\n")
	targetFile.write("#angle:60\n")
	targetFile.write("#image:"+str(eachImage)+"\n") # to correct
	targetFile.write("#anglestep:1\n")
	targetFile.write("#user:kelu124\n")
	targetFile.write("#module:croaker-feather\n")
	targetFile.write("# \n")
	targetFile.write("# Data file created: from the echomods project \n")
	targetFile.write("# Original log files: "+str(startingpoint)+"\n")
	targetFile.write("# See the tools at: https://github.com/kelu124/echomods/tree/master/croaker/data/raw_data/"+"\n")
	targetFile.write("# \n")

	# Saving the image
	outfile = filename +"-"+str(eachImage)+".png"
	im.save(outfile) 
	targetFile.close()

