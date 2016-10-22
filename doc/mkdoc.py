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
# Get icons for compiler log
# -------------------------

log = []
GreenMark = ":white_check_mark:"
RedMark = ":no_entry:"
WarningMark = ":warning:"
ValidH = ["h1","h2","h3","h4","h5"]

ModulesChaptDeux = ["tobo","retroATL3","mogaba","goblin","tobo","toadkiller"]
ModulesChaptTrois = ["silent","cletus","croaker","doj","sleepy","oneeye"]

# -------------------------
# Graph support
# -------------------------

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

def GetListofModules(dirname):
	ExcludeDirs = ["include","tools",".git","gh-pages","doc","gitbook"]
	ExcludeDirsRetired = ExcludeDirs+["retired"]
	ListOfDirs = os.listdir(dirname)  
	ModulesDirs = []
	for f in ListOfDirs:
		if  os.path.isdir(dirname+"/"+f):
			ModulesDirs.append(f)
	# On retire les repertoires non modules
	if ("retired" not in dirname):
		f = [x for x in ModulesDirs if x not in ExcludeDirsRetired]
	else:
		f = [x for x in ModulesDirs if x not in ExcludeDirs]
	return f



def getText(path):
	f = open(path,'r')
	text = f.read()+"\n"
	f.close()
	return text

def returnSoup(path):
	f = open(path, 'r')
	RawHTML=markdown.markdown( f.read() )
	f.close()
	return [BeautifulSoup(RawHTML,"lxml"),RawHTML]

def getHs(soup,h,hText):
	Text = BeautifulSoup("", "lxml")
	if (h in ValidH):
		allH = soup.find_all(h)
		for H in allH:
			if hText in H:
 				nextSib = H.find_next(True)
   				while nextSib is not None and "h" not in nextSib.name :
					Text.append(nextSib)
               				nextSib = nextSib.nextSibling
	return Text


def returnHList(soup,h,hText):
	ListItem = []
	if (h in ValidH):
		desch3 = soup.find_all(h)
		for H in desch3:
			if hText in H.text:
			    for item in H.find_next("ul").find_all("li"):
				ListItem.append(item)
	else:
		print "H Error"
	return ListItem

def getCode(string):
	ListOfCodes = []
	for item in string.find_all("code"):
		ListOfCodes.append(item.text)
	return ListOfCodes


def GitBookizeModule(s,module):
	t = s.split("\n## ")
	del t[1]
	titreModule = t[1]
	titreModule = titreModule.replace("\n","").replace("Title","")
	del t[1]
	del t[1]
	del t[1]
	del t[1]
	del t[-1]
	del t[-1]
	del t[0]	
	joiner = "\n## "
	u = joiner.join(t)

	u = "## "+u.replace("![Block schema](source/blocks.png)","![Block schema](https://raw.githubusercontent.com/kelu124/echomods/master/"+module+"/source/blocks.png)")


	HeaderModule = "# "+titreModule+ "\n\n ## What does it look like? \n\n <img src='https://raw.githubusercontent.com/kelu124/echomods/master/"+module+"/viewme.png' align='center' width='150'>\n\n"

	u = HeaderModule+ u
	return u


def SearchString(s, leader, trailer):
  end_of_leader = s.index(leader) + len(leader)
  start_of_trailer = s.index(trailer, end_of_leader)
  return s[end_of_leader:start_of_trailer]

def AddOneLevel(s):
	return s.replace("# ", "## ")

def AddTwoLevels(s):
	return s.replace("# ", "### ")

def WorkLogLevel(s):
	return s.replace("#### ", "## ")

def IncludeImage(s):
	return s.replace("<img src='https://github.com/kelu124/echomods/blob/master/", "<img src='https://raw.githubusercontent.com/kelu124/echomods/master/")

def AddRawHURL(s):
	BaseURL = "https://kelu124.gitbooks.io/echomods/content"
	URL = "https://raw.githubusercontent.com/kelu124/echomods/master/"
	for moduledeux in ModulesChaptDeux:
		s = s.replace("](/"+moduledeux+"/)", "]("+BaseURL+"/Chapter2/"+moduledeux+".md)")	
		s = s.replace("](/"+moduledeux+"/source/blocks.png)", "](https://raw.githubusercontent.com/kelu124/echomods/master/"+moduledeux+"/source/blocks.png)")	
		s = s.replace("](/"+moduledeux+"/Readme.md)", "]("+BaseURL+"/Chapter2/"+moduledeux+".md)")
	for moduletrois in ModulesChaptTrois:
		s = s.replace("](/"+moduletrois+"/)", "]("+BaseURL+"/Chapter3/"+moduletrois+".md)")	
		s = s.replace("](/"+moduletrois+"/Readme.md)", "]("+BaseURL+"/Chapter3/"+moduletrois+".md)")
		s = s.replace("](/"+moduletrois+"/source/blocks.png)", "](https://raw.githubusercontent.com/kelu124/echomods/master/"+moduletrois+"/source/blocks.png)")	

	return s.replace("![](/", "![]("+URL)

def AddRawMurgenURL(s):
	ListOfMurgenSessions = ["Session_1.md","Session_2.md","Session_3.md","Session_4.md","Session_4b.md","Session_5.md","Session_6.md","Session_7.md","Session_8.md","Session_9_ATL.md",]
	BaseURL = "https://kelu124.gitbooks.io/echomods/content"
	URL = "https://raw.githubusercontent.com/kelu124/murgen-dev-kit/master/"
	for Session in ListOfMurgenSessions:
		s = s.replace("](/worklog/"+Session+")", "]("+BaseURL+"/Chapter4/"+Session+")")	
	s= re.sub('!\[.*\]', '![]', s)
	return s.replace("![](/", "![]("+URL)


def OpenWrite(Write,Open):
	f = open(Open,"w+")
	f.write(Write)
	return f.close()


def GraphModule(Paires,GraphThisModule,ReadMe):
        for eachPair in Paires:
	    eachPair = eachPair.text
	    if ("->" in eachPair):
	   	Couples = eachPair.split("->")
		for single in Couples:
		    GraphThisModule.node(single, style="rounded")
		# Add the edge		
		for k in range(len(Couples)-1):
		    GraphThisModule.edge(Couples[k], Couples[k+1])
	GraphThisModule.render(ReadMe+'/source/blocks')
	Svg2Png(ReadMe+'/source/blocks')

