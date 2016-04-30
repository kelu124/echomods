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

# -------------------------
# Aide pour le graphe
# -------------------------

graph = functools.partial(gv.Graph, format='svg')
digraph = functools.partial(gv.Digraph, format='svg')

GraphModules = digraph()

def Svg2Png(svgfile):
	output_filename = svgfile+'.png'
	input_filename = svgfile+'.svg'

	svg_file = open(input_filename,"r")

	with wand.image.Image() as image:
	    with wand.color.Color('transparent') as background_color:
		library.MagickSetBackgroundColor(image.wand, background_color.resource) 
	    image.read(blob=svg_file.read())
	    png_image = image.make_blob("png32")

	with open(output_filename, "wb") as out:
	    out.write(png_image)

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
	GraphModules.node(eachInput, style="filled", fillcolor="blue", shape="box",fontsize="22")


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

TableModules += "| ThumbnailImage | Name | In | Out |\n"
TableModules += "|------|-------|----|------|\n"

for ReadMe in ListOfDirs:
	f = open(ReadMe+"/Readme.md", 'r')
	ReadMehHtmlMarkdown=markdown.markdown( f.read() )
	f.close()

	# Getting the Desc of the Module
	pattern = r"</h2>([\s\S]*)<h2>How"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<p>(.*?)</p>"
	Desc = []
	for item in results:
	    Desc = map(str, re.findall(patternCode, item, flags=0))
	Desc = Desc[0]

	# Getting the Innards of the Module
	pattern = r"block diagram</h2>([\s\S]*)<h1>IOs"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<li>(.*?)</li>"
	Pairs = []
	GraphThisModule = digraph()
	for item in results:
            Pairs= (map(str, re.findall(patternCode, item, flags=0)))
	    for eachPair in Pairs:
		eachPair = eachPair.replace("<code>", "")
		eachPair = eachPair.replace("</code>", "")
		Couples = eachPair.split("-&gt;")		
		for single in Couples:
		    GraphThisModule.node(single, style="rounded")
		# Add the edge		
		for k in range(len(Couples)-1):
		    GraphThisModule.edge(Couples[k], Couples[k+1])
		# GraphModules.render('include/'+ReadMe)
	GraphThisModule.render(ReadMe+'/source/blocks')
	Svg2Png(ReadMe+'/source/blocks')

	# Getting the Inputs of the Module
	pattern = r"Inputs</h2>([\s\S]*)<h2>Outputs"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<code>(.*?)</code>"
	Inputs = []
	for item in results:
	    Inputs = map(str, re.findall(patternCode, item, flags=0))
	    for eachInput in Inputs:
		if "ITF-m" not in eachInput:
		    GraphModules.node(eachInput, style="rounded,filled", fillcolor="yellow")
		else:
		    GraphModules.node(eachInput, style="rounded,filled", fillcolor="green")		
		GraphModules.edge(eachInput, ReadMe, splines="line", nodesep="1")
	inpoots = ", ".join( Inputs )
	


	# Getting the Ouputs of the Module
	pattern = r"Outputs</h2>([\s\S]*)<h1>Key"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<code>(.*?)</code>"
	Outputs = []
	for item in results:
	    Outputs = map(str, re.findall(patternCode, item, flags=0))
	    for eachOutput in Outputs:
		if "ITF-m" not in eachOutput:
		    GraphModules.node(eachOutput, style="rounded,filled", fillcolor="yellow")
		else:
		    GraphModules.node(eachOutput, style="rounded,filled", fillcolor="green")
		GraphModules.edge(ReadMe, eachOutput, splines="line", nodesep="1", fillcolor="red")
	outpoots = ", ".join( Outputs )



	TableModules += "|<img src='https://github.com/kelu124/echomods/blob/master/"+ReadMe+"/viewme.png' align='center' width='150'>|**["+ReadMe+"](/"+ReadMe+"/Readme.md)**: "+Desc+"|"+inpoots+"|"+outpoots+"|\n"


TableDocTxt = TableModules+"\n\n"

# -------------------------
# Créer le graphe des modules
# -------------------------

GraphPath = 'include/ModulesGraph'
GraphModules.render(GraphPath)
Svg2Png(GraphPath)


# -------------------------
# Créer le ReadMe
# -------------------------


GraphModulesTxt = "\n# The modules organization \n\n"

GraphModulesTxt += "![Graph](/include/ModulesGraph.png) \n\n"

FinalDoc =  HeaderDocTxt+GraphModulesTxt+TableDocTxt+AddInterfacesDocTxt+AddLicenseDocTxt

f = open("Readme.md","w+")
f.write(FinalDoc)
f.close()



# -------------------------
# ToCome: TODO to add
# -------------------------



