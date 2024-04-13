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

print( 'Number of arguments:', len(sys.argv), 'arguments.')
print( 'Argument List:', str(sys.argv))
edit = 0

if (len(sys.argv) == 2 ):
	FileName = sys.argv[1]
	if not os.path.exists(FileName):
		print( "FileDoesNotExist")
	else:
		metadata = pyexiv2.ImageMetadata(FileName)
		try:
			metadata.read()
		except IOError:
			print( "Not an image")
		else:
			# Modules
			print( "Already here    -> " + bcolors.WARNING + str(metadata['Exif.Image.Software'].value) + bcolors.ENDC)
			input_var = str(input("What modules are present (enter = pass): "))
			if len(input_var):
				edit = 1
				#print "You entered: " + input_var
				metadata['Exif.Image.Software'] = input_var

			# Description
			print( "Already here    -> "  + bcolors.WARNING + str(metadata['Exif.Image.ImageDescription'].value) + bcolors.ENDC)
			input_var = str(input("Description? (enter = pass): "))
			if len(input_var):
				edit = 1
				#print "You entered: " + input_var
				metadata['Exif.Image.ImageDescription'] = input_var
			if edit:
				metadata.write()
				print("Image saved")

			# Experiment
			try:
				metadata['Exif.Image.Make'].value
			except KeyError:
				metadata['Exif.Image.Make'] = ""

			print( "Already here    -> "  + bcolors.WARNING + str(metadata['Exif.Image.Make'].value) + bcolors.ENDC)
			input_var = str(input("Experiment? (enter = pass): "))
			if len(input_var):
				edit = 1
				#print "You entered: " + input_var
				metadata['Exif.Image.Make'] = input_var


			# Type of picture
			try:
				metadata['Exif.Photo.MakerNote'].value
			except KeyError:
				metadata['Exif.Photo.MakerNote'].value = ""

			print ("Already here    -> "  + bcolors.WARNING + str(metadata['Exif.Photo.MakerNote'].value) + bcolors.ENDC)
			input_var = str(input("Type of picture? (enter = pass): "))
			if len(input_var):
				edit = 1
				#print "You entered: " + input_var
				metadata['Exif.Photo.MakerNote'] = input_var

			# Saving the image
			if edit:
				metadata.write()
				print ("Image saved")

else:
	print( "No file passed")
