#!/usr/bin/python

import sys
import pyexiv2
import os

print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)
edit = 0

if (len(sys.argv) == 2 ):
	FileName = sys.argv[1]
	if not os.path.exists(FileName):
		print "FileDoesNotExist"
	else:
		metadata = pyexiv2.ImageMetadata(FileName)
		try:
			metadata.read()
		except IOError:
			print "Not an image"
		else:
			# Modules
			input_var = str(raw_input("What modules are present (enter = pass): "))
			if len(input_var):
				edit = 1
				#print "You entered: " + input_var
				metadata['Exif.Image.Software'] = input_var

			# Description
			input_var = str(raw_input("Description? (enter = pass): "))
			if len(input_var):
				edit = 1
				#print "You entered: " + input_var
				metadata['Exif.Image.ImageDescription'] = input_var
			if edit:
				metadata.write()
				print "Image saved"

else:
	print "No file passed"
