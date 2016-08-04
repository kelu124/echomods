#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# cc-by-sa/4.0/
# -------------------------
# Requires GraphViz and Wand
# -------------------------

import os
import markdown
import re
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

# -------------------------
# Get icons
# -------------------------

GreenMark = ":green_heart:"
RedMark = ":broken_heart:"
WarningMark = ":warning:"

# -------------------------
# Obtenir la liste des modules
# -------------------------

ExcludeDirs = ["include","retired","tools",".git","gh-pages", "doc"]
dirname = os.path.join( os.path.dirname( __file__ ), '..' )
ListOfDirs = os.listdir(dirname)  

ModulesDirs = []
# On itere
for f in ListOfDirs:
	#print dirname+"/"+f
	if  os.path.isdir(dirname+"/"+f):
		
		ModulesDirs.append(f)


# On retire les repertoires non modules
ListOfDirs = [x for x in ModulesDirs if x not in ExcludeDirs]


TableChecks = "# Summary of the test \n\n\n"
TableChecks = "## Structure of the folders\n\n"
TableChecks += "| Module Name | ReadMe | ViewMe | Folders |Module Codename|\n"
TableChecks += "|------|-------|-------|----|----------|----|\n"

ReadmeChecks = "## Structure of the folders\n\n"
ReadmeChecks += "| Module Name | Blocks | TODO | \n"
ReadmeChecks += "|------|------|-------|\n"

# -------------------------
# Iterons sur les modules
# -------------------------

for eachDir in ListOfDirs:
	# Name of the module
	TableChecks += "| "+eachDir+" |"
	ReadmeChecks += "| "+eachDir+ " "
	# Checking Readmes
	if (os.path.isfile(dirname+"/"+eachDir+"/Readme.md")):
		TableChecks += GreenMark + " Readme.md |"
	elif (os.path.isfile(dirname+"/"+eachDir+"/Readme.txt")):
		TableChecks += GreenMark + " Readme.txt |"
	else:
		TableChecks += RedMark + " Failed |"
	# Checking viewme
	if (os.path.isfile(dirname+"/"+eachDir+"/viewme.png")):
		TableChecks += GreenMark + " OK |"
	else:
		TableChecks += RedMark + " Failed |"

	# Listons les folders
	ListOfDirs = os.listdir(dirname+"/"+eachDir)  
	LD = []
	for f in ListOfDirs:
		if  os.path.isdir(dirname+"/"+eachDir+"/"+f):
			LD.append(f)
	if len(LD) == 0:
		TableChecks += WarningMark+ "No folder"
		TableChecks
	else:
		TableChecks += GreenMark +" _"+"_, _".join(LD)+"_"
	TableChecks += "|"
	#print LD

	# Working on the doc itself
	f = open(dirname+"/"+eachDir+"/Readme.md", 'r')
	ReadMehHtmlMarkdown=markdown.markdown( f.read() )
	f.close()
	soup = BeautifulSoup(ReadMehHtmlMarkdown,"lxml")

	# Checks
	#print ReadMehHtmlMarkdown
	desc = soup.find_all("h2")
	ReadmeChecks += "|<ul>"
	# NameCheck	
	NameCheck = ""
	for H2 in desc:
		if "Name" in H2.text:
			NameCheck += "<li>"+GreenMark + " "+H2.find_next("p").text+"</li>"
	if len(NameCheck)==0:
		NameCheck += "<li>"+RedMark + " Name</li>"
	TableChecks += NameCheck

	#print soup

	desc = soup.find_all("h3")
	# Inputs	
	NameCheck = ""
	for H3 in desc:
		if "Inputs" in H3.text:
			NameCheck += "<li>"+GreenMark + " "+str(len(H3.find_next("ul").find_all("li")))+" input(s) </li>"
	if len(NameCheck)==0:
		NameCheck += "<li>"+RedMark + " Inputs</li>"
	ReadmeChecks += NameCheck
	# Outputs	
	NameCheck = ""
	for H3 in desc:
		if "Outputs" in H3.text:
			NameCheck += "<li>"+GreenMark + " "+str(len(H3.find_next("ul").find_all("li")))+" output(s) </li>"
	if len(NameCheck)==0:
		NameCheck += "<li>"+RedMark + " Outputs</li>"
	ReadmeChecks += NameCheck
	ReadmeChecks += "</ul>|"

	## TODOS
	ReadmeChecks += "<ul>"
	# Todo	
	NameCheck = ""
	for H3 in desc:
		if "TODO" in H3.text:
			NameCheck += "<li>"+GreenMark + " "+str(len(H3.find_next("ul").find_all("li")))+" todo(s) </li>"
	if len(NameCheck)==0:
		NameCheck += "<li>"+RedMark + " Todos</li>"
	ReadmeChecks += NameCheck

	# Done
	NameCheck = ""
	for H3 in desc:
		if "DONE" in H3.text:
			NameCheck += "<li>"+GreenMark + " "+str(len(H3.find_next("ul").find_all("li")))+" done(s) </li>"
	if len(NameCheck)==0:
		NameCheck += "<li>"+RedMark + " Todos</li>"
	ReadmeChecks += NameCheck



	TableChecks += "</ul>|\r\n"
	ReadmeChecks += "</ul>|\r\n"


text_file = open("test_results.md", "w")
text_file.write(TableChecks+ReadmeChecks)
text_file.close()


#print ReadmeChecks






