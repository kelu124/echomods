#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# cc-by-sa/4.0/
#
# Library for tagging images
# Definitely not optimized
#
# -------------------------

'''Description: Autotagging images for the `20201219r` experiment.'''

__author__      = "kelu124"
__copyright__   = "Copyright 2018, Kelu124"
__license__ 	= "cc-by-sa/4.0/"


import sys
import pyexiv2
import os
import os.path

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'



# Path
path = os.getcwd().split("/")[-1]

Imgs = []
for dirpath, dirnames, filenames in os.walk("."):
    for filename in [f for f in filenames if ( f.lower().endswith(".jpg") or f.lower().endswith(".png") )]:
        Imgs.append( os.path.join(dirpath, filename) )

print(Imgs)

for FileName in Imgs:
    edit = 0

    metadata = pyexiv2.ImageMetadata(FileName)
    try:
        metadata.read()
    except IOError:
        print("Not an image")
    else:
        # Modules
        metadata['Exif.Image.Software'] = "s3"
        # Experiment - none here
        # metadata['Exif.Image.Make'] = path

        metadata['Exif.Photo.MakerNote'] = "ToTag"
        # Description
        metadata['Exif.Image.ImageDescription'] = "s3 probe"
        # Saving the image

        metadata.write()
        print("Image "+FileName+" saved")

