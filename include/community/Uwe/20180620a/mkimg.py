#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# cc-by-sa/4.0/
#
# Library for creating images from the 
# files created by pulser module.
# Used in `20180620a`
# Definitely not optimized
#
# -------------------------

'''Description: Autotagging images for the `20180620a` experiment.'''

__author__      = "kelu124"
__copyright__   = "Copyright 2018, Kelu124"
__license__ 	= "cc-by-sa/4.0/" 


import sys
import pyexiv2
import os

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

Imgs = []
for dirpath, dirnames, filenames in os.walk("."):
    for filename in [f for f in filenames if ( f.endswith(".jpg") or f.endswith(".png") )]:
        Imgs.append( os.path.join(dirpath, filename) )

print Imgs

for FileName in Imgs:
	edit = 0

	metadata = pyexiv2.ImageMetadata(FileName)
	try:
		metadata.read()
	except IOError:
		print "Not an image"
	else:
		# Modules
		metadata['Exif.Image.Software'] = "elmo"
		# Experiment
		metadata['Exif.Image.Make'] = "20180620a"

		# Type of picture
		if "line" in FileName:
			metadata['Exif.Photo.MakerNote'] = "graph"
			# Description
			metadata['Exif.Image.ImageDescription'] = "Checking raw signal"
		elif "IMAG" in FileName:
			metadata['Exif.Photo.MakerNote'] = "setup"
			# Description
			metadata['Exif.Image.ImageDescription'] = "Setup of the experiment"
		elif "DAT" in FileName:
			metadata['Exif.Photo.MakerNote'] = "other"
			# Description
			metadata['Exif.Image.ImageDescription'] = "Other files"
		
		# Saving the image

		metadata.write()
		print "Image "+FileName+" saved"

