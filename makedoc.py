#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import markdown
import re
import graphviz as gv
import functools



# -------------------------
# Aide pour le graphe
# -------------------------

graph = functools.partial(gv.Graph, format='svg')
digraph = functools.partial(gv.Digraph, format='svg')

GraphModules = digraph()

# -------------------------
# Obtenir la liste des modules
# -------------------------

ExcludeDirs = ["include","tools",".git"]
dirname = "./"
ListOfDirs = os.listdir(dirname)  
ModulesDirs = []
# On itere
for f in ListOfDirs:
	if  os.path.isdir(f):
		ModulesDirs.append(f)
# On retire les repertoires non modules
ListOfDirs = [x for x in ModulesDirs if x not in ExcludeDirs]



for eachInput in ListOfDirs:
	GraphModules.node(eachInput, style="filled", fillcolor="blue", shape="box")


# -------------------------
# Files includes
# -------------------------

HeaderDoc = open("include/AddEchomods.md")
HeaderDocTxt = HeaderDoc.read()+"\n\n"
HeaderDoc.close()
AddInterfacesDoc = open("include/AddInterfaces.md")
AddInterfacesDocTxt = AddInterfacesDoc.read()+"\n\n"
AddInterfacesDoc.close()
AddLicenseDoc = open("include/AddLicense.md")
AddLicenseDocTxt = AddLicenseDoc.read()+"\n\n"
AddLicenseDoc.close()


# -------------------------
# Préparer un tableau de présentation
# -------------------------

TableModules = "# A recap of our modules \n\n\n"

TableModules += "| Image | Name | In | Out |"
TableModules += "|------|-------|----|------|"

for ReadMe in ListOfDirs:
	f = open(ReadMe+"/Readme.md", 'r')
	ReadMehHtmlMarkdown=markdown.markdown( f.read() )
	f.close()

	# Getting the Desc of the Module
	pattern = r"</h2>([\s\S]*)<h2>How"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<p>(.*?)</p>"
	for item in results:
	    Desc = map(str, re.findall(patternCode, item, flags=0))
	    Desc = " ".join( Desc )

	# Getting the Inputs of the Module
	pattern = r"Inputs</h2>([\s\S]*)<h2>Outputs"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<code>(.*?)</code>"
	for item in results:
	    Inputs = map(str, re.findall(patternCode, item, flags=0))
	    for eachInput in Inputs:
		#GraphModules = add_nodes(GraphModules, eachInput)
		GraphModules.node(eachInput, style="rounded,filled", fillcolor="yellow")
		GraphModules.edge(eachInput, ReadMe)
	inpoots = ", ".join( Inputs )
	


	# Getting the Ouputs of the Module
	pattern = r"Outputs</h2>([\s\S]*)<h1>Key"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<code>(.*?)</code>"
	for item in results:
	    Outputs = map(str, re.findall(patternCode, item, flags=0))
	    for eachOutput in Outputs:
		GraphModules.node(eachOutput, style="rounded,filled", fillcolor="yellow")
		GraphModules.edge(ReadMe, eachOutput, style="filled", fillcolor="red")
	outpoots = ", ".join( Outputs )

	TableModules += "|![Thumb](/"+ReadMe+"/viewme.png)|**["+ReadMe+"](/"+ReadMe+"/Readme.md)**: "+Desc+"|"+inpoots+"|"+outpoots+"|\n"


TableDocTxt = TableModules+"\n\n"

# -------------------------
# Créer le graphe des modules
# -------------------------


GraphModules.render('include/ModulesGraph')

GraphModulesTxt = "# A recap of our modules \n\n"
GraphModulesTxt = "![Graph](/include/ModulesGraph.svg) \n\n"

FinalDoc =  HeaderDocTxt+GraphModulesTxt+TableDocTxt+AddInterfacesDocTxt+AddLicenseDocTxt

f = open("Readme.md","w+")
f.write(FinalDoc)
f.close()

