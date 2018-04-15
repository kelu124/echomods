#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# cc-by-sa/4.0/
# -------------------------
# Retirement
# -------------------------

'''Description: Retire old modules.'''

__author__      = "kelu124"
__copyright__   = "Copyright 2016, Kelu124"
__license__ 	= "cc-by-sa/4.0/"

import chardet   
import os
import os.path, time
from glob import glob
import markdown
import re
import pyexiv2
import graphviz as gv
import functools
# Wand for SVG to PNG Conversion
from wand.api import library
import wand.color
import wand.image
import Image
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
from bs4 import BeautifulSoup
import urllib2
from datetime import datetime

path = "./"
results = [y for x in os.walk(path) for y in glob(os.path.join(x[0], '*.md'))]+[y for x in os.walk(path) for y in glob(os.path.join(x[0], '*.tpl'))]
ExcludeDirs = ["tools",".git","gh-pages","doc"]
f = [x for x in results if x.split("/")[1] not in ExcludeDirs]
for eachMd in f:

	fileN = open(eachMd,"r+") 
	MDText = fileN.read() 
	print MDText
	fileN.seek(0)
	MDText = MDText.replace("(/tobo/","(/retired/tobo/")
	MDText = MDText.replace("(/alt.tbo/","(/retired/alt.tbo/")
	MDText = MDText.replace("(/cletus/","(/retired/cletus/")
	MDText = MDText.replace("(/croaker/","(/retired/croaker/")
	MDText = MDText.replace("(/loftus/","(/retired/loftus/")
	MDText = MDText.replace("(/tomtom/","(/retired/tomtom/")
	fileN.write(MDText)
	fileN.truncate()
	fileN.close()




