import sys
import numpy as np
from operator import itemgetter, attrgetter
import Image
from math import *
import math
import scipy.misc
# Prend en argument un fichier .data



data = "20161217-222737-"


k=0
Tableau = []
for i in range(4):
	startingpoint = data+str(i)+".csv"

	with open(startingpoint, 'r') as echOpenLog:
		for line in echOpenLog:
		    if(not line.startswith("#")):
			line = line.split(';')	
			del line[-1]
			Tableau.append(line)

	del Tableau[-1]

	
	SortedTable = Tableau
	PointsPerLine = len(SortedTable[0])
	
NbOfLinesOriginal = 60
NbOfLines = len(SortedTable)
print NbOfLines
PointsPerLine = len(SortedTable[0])
print PointsPerLine

print "==="
print NbOfLinesOriginal
print NbOfLines
print PointsPerLine
rebuilt = np.zeros(shape=(NbOfLines,PointsPerLine))
print str(len(rebuilt))+"/"+str(len(rebuilt[0]))

for i in range(NbOfLinesOriginal):
	for j in range(PointsPerLine):
 		print (i,j)
		rebuilt[4*i][j] = SortedTable[i][j]
		rebuilt[4*i+1][j] = SortedTable[60+i][j]
		rebuilt[4*i+2][j] = SortedTable[120+i][j]
		rebuilt[4*i+3][j] = SortedTable[180+i][j]

print rebuilt

 
scipy.misc.imsave(data+"img.jpg", rebuilt)


 



# Creation d'un fichier donnees
st = data+"total.csv"
targetFile = open(st, 'w')

#Boucles
for i in range(NbOfLines): # les lignes
    for j in range(PointsPerLine):
	value = int(rebuilt[i][j])
	if(j==(PointsPerLine-1)):
		targetFile.write(str(value))
	else:
		targetFile.write(str(value)+";")
    targetFile.write("\n")

targetFile.write("# More details:\n")
targetFile.write("#timestamp:20161217-222737\n")
targetFile.write("#originalfilename:"+str(startingpoint)+"\n")
targetFile.write("#lines:"+str(NbOfLines)+"\n")
targetFile.write("#length:"+str(PointsPerLine)+"\n")
targetFile.write("#frequency:unknown-feather\n")
targetFile.write("#piezofrequency:3500000\n")
targetFile.write("#angle:60\n")
targetFile.write("#anglestep:1/4\n")
targetFile.write("#user:kelu124\n")
targetFile.write("#module:croaker-feather\n")
targetFile.write("# \n")
targetFile.write("# Data file created: from the echomods project \n")
targetFile.write("# Original log files: "+str(startingpoint)+"\n")
targetFile.write("# See the tools at: https://github.com/kelu124/echomods/tree/master/croaker/data/20161217/"+"\n")
targetFile.write("# \n")


targetFile.close()

