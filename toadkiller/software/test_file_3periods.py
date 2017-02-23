#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# cc-by-sa/4.0/
# -------------------------

'''Description: showing content of a PRUDAQ binary dump over 3 periods.'''

__author__      = "kelu124"
__copyright__   = "Copyright 2016, Kelu124"
__license__ 	= "cc-by-sa/4.0/"

import struct
import matplotlib.pyplot as plt
import numpy as np

BinFile = "afreen.bin"

bytes_read = open(BinFile, "rb").read()

i = 0
k = 0
data = []
autredata = []
lb = 0
hb = 0
with open(BinFile, "rb") as f:
    byte = f.read(1)
    while byte != "" and k < (24*12000):
        # Do stuff with byte.
        byte = f.read(1)
	if len(byte)>0:
		i = (i+1)%4
		if (k%1000000 == 0):
			print k/1000000
		k = k+1
		if (i==0):
			lb = ord(byte)
		elif (i==1):
			hb = ord(byte)
		elif (i==2):
			data.append(hb*256+lb)
		#print i

print data
print len(data)


plt.plot(data)  # on utilise la fonction sinus de Numpy
plt.show()
