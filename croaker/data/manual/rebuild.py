import sys
import numpy as np
from operator import itemgetter, attrgetter
import Image
from math import *
import math

# Prend en argument un fichier .data

try:
    sys.argv[1]
except NameError:
    startingpoint = 'Missing an arg'
else:
    startingpoint = sys.argv[1]

Tableau = []
BaseData = [] 

Tableau = []
k=0

with open(startingpoint, 'r') as echOpenLog:
	for line in echOpenLog:
	    if(line.startswith("#")):
		print "Thats a comment"
	    else:
		line = line.split(';')	
		Tableau.append(line)

del Tableau[-1]

SortedTable = Tableau
PointsPerLine = len(SortedTable[0])
NbOfLines = len(SortedTable)
