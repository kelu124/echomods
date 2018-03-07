import csv
import re
from si_prefix import si_format

Param = ["Designator","X-Loc","Y-Loc","Rotation","Side","Type","X-Size","Y-Size","Value","Footprint","Populate","MPN"]

BOM = ["Reference Designator","Voltage","Package","Symbol Type"]
# Manufacturer Part Number-> Inductor, Capacitor, Resistor
DATA = {}
 


DNP = []


with open('77c1d00889d46acf_15124824574958_BOM.csv') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',', quotechar='"')

	done = False
	Header = []
	for row in spamreader:
	    if not done:
		Header = row
	    L = len(row)
	    #print row[1]
	    Item = {}
	    if "Reference" not in str(row[0]) and "DNP" not in row[1]:
	    	for i in range(L):
		#print row[i]

			DATA[row[0]] = {}
			Item[Header[i]] = row[i].strip()
	    #print Item.keys()

	        Item["Footprint"] = re.sub("[\(\[].*?[\)\]]", "", Item["Package"]).strip()  

		if "Capacitor" in Item["Description"]:
			s = Item["Description"]
			R = s[s.rfind("(")+1:s.rfind("F)")] 
			Item["CleanValue"] = si_format(float(R)).replace(" ","").replace(".0","")+"F"
			Item["Cleaned"] = True
		elif "Resistor" in Item["Description"]:
			s = Item["Description"]
			R = s[s.rfind("(")+1:s.rfind(")")]
			if "R" in R:
				R = R[:-1]
			elif "2K2" in R:
				R = "2200" 
			Item["CleanValue"] = si_format(float(R)).replace(" ","").replace(".0","") 
			Item["Cleaned"] = True
		elif "Inductor" in Item["Description"]:
			s = Item["Description"]
			R = s[s.rfind("(")+1:s.rfind("H)")]
			Item["CleanValue"] = si_format(float(R)).replace(" ","").replace(".0","")+"H"
			Item["Cleaned"] = True
		else:
			Item["CleanValue"] = row[3]
			Item["Cleaned"] = False

	        DATA[row[0]] = Item
	    #DATA[Item["Reference Designator"]] = {}
	    else:
		DNP.append(row[0])
	    done = True

print DNP

with open('77c1d00889d46acf_15124824574958_pickplace.csv') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',', quotechar='"')
	for row in spamreader:
	    if "Part" not in row[0] and row[0] not in DNP:
		DATA[row[0]]["X"] = row[1]
		DATA[row[0]]["Y"] = row[2]
		DATA[row[0]]["Rotation"] = row[3]
		DATA[row[0]]["Side"] = row[4]
		if "SMD" in row[5]:
			DATA[row[0]]["Type"] = "1"
		else:
			DATA[row[0]]["Type"] = "2"
		DATA[row[0]]["XSize"] = row[6]
		DATA[row[0]]["YSize"] = row[7]
		DATA[row[0]]["Value2"] = row[8]
		DATA[row[0]]["Footprint"] = row[9]

TAB = "\t"
# #Designator X-Loc Y-Loc Rotation Side Type X-Size Y-Size Value Footprint Populate MPN
CSV = "#Designator\tX-Loc\tY-Loc\tRotation\tSide\tType\tX-Size\tY-Size\tValue\tFootprint\tPopulate\tMPN\n"
for component in DATA.keys():
	LINE = [] 
	#if DATA[component]["Value2"] not in DATA[component]["CleanValue"]:
	#	print component + " - "+ DATA[component]["CleanValue"] + " vs "+ DATA[component]["Value2"]
	LINE.append(component)
	LINE.append(DATA[component]["X"])
	LINE.append(DATA[component]["Y"])
	LINE.append(DATA[component]["Rotation"])
	LINE.append(DATA[component]["Side"])
	LINE.append(DATA[component]["Type"])
	LINE.append(DATA[component]["XSize"])
	LINE.append(DATA[component]["YSize"])
	LINE.append(DATA[component]["CleanValue"])
	LINE.append(DATA[component]["Footprint"])
	LINE.append("1") # for populate
	if DATA[component]["Cleaned"]:
		LINE.append(DATA[component]["CleanValue"]+" "+DATA[component]["Footprint"])
	else:
		LINE.append(DATA[component]["CleanValue"])
	CSV += TAB.join(LINE)
	CSV += "\n"

#
file = open("out.xyrs", "w")
file.write(CSV)
file.close()




#print DATA.keys() 
print "-"+DATA["C5"]["Footprint"]+"-"
