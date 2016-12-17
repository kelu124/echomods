#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# cc-by-sa/4.0/
# -------------------------

'''Description: Takes a log file and creatse the Scan Converted image.'''

__author__      = "kelu124"
__copyright__   = "Copyright 2016, Kelu124"
__license__ 	= "cc-by-sa/4.0/"

import sys
import numpy as np
from operator import itemgetter, attrgetter
import Image
from math import *
import math

# Prend en argument un fichier au bon format echopen (CSV enrichi)

try:
    sys.argv[1]
except NameError:
    startingpoint = 'Missing an arg'
else:
    startingpoint = sys.argv[1]

Tableau = []
BaseData = []
DECIMATION = 1 	# Should we do a basic summation on the pixels, hence reducing the noice and the size of the picture?

Tableau = []
k=0

with open(startingpoint, 'r') as echOpenLog:
	for line in echOpenLog:
	    if(line.startswith("#")):
		#print "commentaire"		
		ikl = 0
	    else:
		line = line.split(';')	
		Tableau.append(line)

SortedTable = Tableau


print SortedTable
print len(SortedTable)
print len(SortedTable[0])

for i in range(len(SortedTable)): # les lignes
    print i
    del SortedTable[i][-1]

PointsPerLine = len(SortedTable[0])
NbOfLines = len(SortedTable)

print SortedTable

# Debugging the image creation
print PointsPerLine 	# 2100
print NbOfLines 	# 59


SortedTable = np.array(SortedTable).astype(int)
#SortedTable = SortedTable[np.argsort(SortedTable[:,0])]
print SortedTable

# Refaire l'image
Depth = PointsPerLine
size = (NbOfLines,(int)(Depth/((DECIMATION))))  

ImagePoints=np.zeros(shape=(NbOfLines,Depth/DECIMATION))
ImagePoints = np.array(ImagePoints).astype(int)



#Prepare the png image
im = Image.new('RGB',size)
pix = im.load()


	
# Creation d'une image non scan-converted
for i in range(size[0]): # les lignes
    for j in range(size[1]):
 
	value = 0
	for k in range(DECIMATION):
		value = value + SortedTable[i][j*DECIMATION+k]*(1.9*(j*DECIMATION+k)**(0.6)/(Depth**(0.6)))
	
	value = (int)(value/DECIMATION)
	print value
	ImagePoints[i][j] = value/64
        pix[i,j] = (ImagePoints[i][j],ImagePoints[i][j],ImagePoints[i][j]) 


outfile = startingpoint +"-DEC"+str(DECIMATION)+".png"
im.save(outfile)


# Doing a basic ScanConversion, on 120 lines images
if True: #comment
	maxAngle = 50.0
	step = 2.0*maxAngle/(NbOfLines+1)
	size = (NbOfLines,PointsPerLine)

	X=np.zeros(shape=(size[0],size[1]))
	Y=np.zeros(shape=(size[0],size[1]))
	for i in range(size[0]):
	    for j in range(size[1]):
		X[i][j] = j*math.cos(math.radians(step*i-maxAngle)) 
		Y[i][j] = (size[1]+1)/2.0+j*math.sin(math.radians(step*(i)-maxAngle)) # same
	print int(size[1]*math.cos(math.radians(maxAngle)))
		

	MaxDepth = int(size[1]*math.cos(math.radians(30)))

	sizeSC = (size[1],size[1])
	ScanConverted=np.zeros(shape=(size[1],size[1]))
	ScanConverted = ScanConverted + 40
	im = Image.new('RGB',(size[1],size[1]))
	pix = im.load()
	print sizeSC
	for i in range(size[1]):
	    for j in range(size[1]):
		value = 128
		pix[i,j] = (value,value,value)

	for i in range(size[1]):
	    if (i<MaxDepth):
		    if (i>=0 & i<=(size[1])):
			    sweep = int(i*(254/2)/220)
			    for j in range((size[1]/2-sweep),(size[1]/2+sweep)):
				D = (X-i)**2 + (Y-j)**2
				resul = np.unravel_index(D.argmin(), D.shape)
				# here is a basic NN, not even a 2-tap
				ScanConverted[i][j] = ImagePoints[resul[0]][resul[1]]
				#print value
				value = int(ScanConverted[i][j])
				pix[j,i] = (value,value,value)
		    print i 
	    else:
		for j in range(size[1]):
		    if ( (i**2) + (j-(size[1]/2))**2 ) < ((size[1])**2 - 1):
				D = (X-i)**2 + (Y-j)**2
				resul = np.unravel_index(D.argmin(), D.shape)
				# here is a basic NN, not even a 2-tap
				ScanConverted[i][j] = ImagePoints[resul[0]][resul[1]]
				value = int(ScanConverted[i][j])
				#print value
				pix[j,i] = (value,value,value)
		print i 
	outfile = startingpoint +"-DEC"+str(DECIMATION)+"-SC.png"
	im.save(outfile)



