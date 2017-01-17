#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -------------------------
# (c) kelu124
# cc-by-sa/4.0/
# -------------------------
# Requires GraphViz and Wand
# -------------------------

''' .'''

__author__      = "kelu124"
__copyright__   = "Copyright 2016, Kelu124"
__license__ 	= "cc-by-sa/4.0/"

import os
from glob import glob
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
import urllib2

graph = functools.partial(gv.Graph, format='svg')
digraph = functools.partial(gv.Digraph, format='svg')

# -------------------------
# Graph customised
# -------------------------

styles = {
    'graph': {
        'label': 'Mapping FDA 510(k)',
	#'layout':"neato",
	'fontsize':"26",
	"splines":"ortho",
	'outputorder':'edgesfirst',
	"rankdir":"LR",
	"overlap":"false",
        #'rankdir': 'BT',
    }
}


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

def apply_styles(graph, styles):
    graph.graph_attr.update(
        ('graph' in styles and styles['graph']) or {}
    )
    graph.node_attr.update(
        ('nodes' in styles and styles['nodes']) or {}
    )
    graph.edge_attr.update(
        ('edges' in styles and styles['edges']) or {}
    )
    return graph


def GraphModule(Paires,GraphThisModule):
    #print Paires
    if ("->" in Paires):
   	Couples = Paires.split("->")
	Couples = [word.strip() for word in Couples]
	for single in Couples:
	    GraphThisModule.node(single, style="rounded")
	# Add the edge		
	for k in range(len(Couples)-1):
	    GraphThisModule.edge(Couples[k], Couples[k+1].strip())

def GraphLabel(Paires,GraphThisModule):
    #print Paires
    if (":" in Paires):
   	Couples = Paires.split(":")
	Couples = [word.strip() for word in Couples]
        GraphThisModule.node(Couples[0], label=Couples[1], style="filled", fillcolor="yellow", shape="box")



def GetFiles(path,extension):
	return [y for x in os.walk(path) for y in glob(os.path.join(x[0], '*.'+extension))]
	 



List = GetFiles("./","template")

print List



for item in List:
	with open(item,'r') as f:
	    GraphModules = digraph()
	    output = f.readlines()
	    for line in output:
		if ("->" in line):
			GraphModule(line,GraphModules)
		if (":" in line):
			GraphLabel(line,GraphModules)
	    name = item.split("./")[1].split(".")[0]

	    apply_styles(GraphModules,styles)

	    GraphModules.render(name)	
	    Svg2Png(name) 




