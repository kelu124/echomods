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

import os

# -------------------------
# Aide pour le graphe
# -------------------------

graph = functools.partial(gv.Graph, format='svg')
digraph = functools.partial(gv.Digraph, format='svg')

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
# Et ... go !
# -------------------------

for file in os.listdir("./"):
    if file.endswith(".set.md"):
	ListOfDirs = []
	NomDuSet = file[:-7]
	print "'"+NomDuSet+"'"
	with open(file) as f:
	    for line in f:
		line = line.rstrip('\r\n').rstrip('\n')
		if len(line)>1 and not line.startswith("#"):
			ListOfDirs.append(line)
			print "-> '"+line+"'"

	GraphModules = digraph()
	# Dans chaque sous-ensemble..
	for eachInput in ListOfDirs:
		GraphModules.node(eachInput, style="filled", fillcolor="blue", shape="box",fontsize="22")
	for ReadMe in ListOfDirs:
		f = open("./../"+ReadMe+"/Readme.md", 'r')
		ReadMehHtmlMarkdown=markdown.markdown( f.read() )
		f.close()


		# Getting the Desc of the Module
		pattern = r"</h3>([\s\S]*)<h3>How"
		results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
		patternCode = r"<p>(.*?)</p>"
		Desc = []
		for item in results:
		    Desc = map(str, re.findall(patternCode, item, flags=0))
		#print Desc
		Desc = Desc[0]

		# Getting the Innards of the Module // inside the block diagram
		pattern = r"block diagram</h3>([\s\S]*)<h2>About"
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

		# Getting the Inputs of the Module
		pattern = r"Inputs</h3>([\s\S]*)<h3>Outputs"
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

		# Getting the Ouputs of the Module
		pattern = r"Outputs</h3>([\s\S]*)<h2>Key"
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



		GraphPath = "./sets/"+NomDuSet
		GraphModules.render(GraphPath)
		Svg2Png(GraphPath)
