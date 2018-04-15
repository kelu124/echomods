#!/usr/bin/python

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
for filename in os.listdir("./"):
    if filename.endswith(".jpg"):
        Imgs.append(os.path.join("./", filename))
    if filename.endswith(".png"):
        Imgs.append(os.path.join("./", filename))

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
		metadata['Exif.Image.Software'] = "elmo, tomtom, alt.tbo, doj, goblin, cletus"

		# Description
		metadata['Exif.Image.ImageDescription'] = "Testing the alt.tbo pulser with a simple piezo"


		# Experiment
		metadata['Exif.Image.Make'] = "20171111a"


		# Type of picture
		if "Spectre" in FileName:
			metadata['Exif.Photo.MakerNote'] = "signal"

		# Saving the image

		metadata.write()
		print "Image "+FileName+" saved"

