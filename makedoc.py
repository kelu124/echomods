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

ExcludeDirs = ["include","retired","tools",".git","gh-pages"]
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
	pattern = r"</h3>([\s\S]*)<h3>How"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<p>(.*?)</p>"
	Desc = []
	for item in results:
	    Desc = map(str, re.findall(patternCode, item, flags=0))
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
	GraphThisModule.render(ReadMe+'/source/blocks')
	Svg2Png(ReadMe+'/source/blocks')

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
	if len(Inputs) > 0:
		inpoots = "<ul><li>"+"</li><li>".join( Inputs )+"</li></ul>"
	else:
		inpoots = ""
	


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
	if len(Outputs) > 0:
		outpoots = "<ul><li>"+"</li><li>".join( Outputs )+"</li></ul>"
	else:
		outpoots = ""


	TableModules += "|<img src='https://github.com/kelu124/echomods/blob/master/"+ReadMe+"/viewme.png' align='center' width='150'>|**["+ReadMe+"](/"+ReadMe+"/Readme.md)**: "+Desc+"|"+inpoots+"|"+outpoots+"|\n"

TableDocTxt = TableModules+"\n\n"

# -------------------------
# Créer le tableau d'avancement
# -------------------------

TableAvancement = "# Progress on building the modules \n\n\n"

TableAvancement += "| Name of module | ToDo | Done | Contrib | Progress |\n"
TableAvancement += "|------|-------|----|------|------|\n"


for ReadMe in ListOfDirs:
	f = open(ReadMe+"/Readme.md", 'r')
	ReadMehHtmlMarkdown=markdown.markdown( f.read() )
	f.close()
	#print ReadMehHtmlMarkdown
	# Getting the todo-list for the module
	pattern = r"Discussions</h2>([\s\S]*)<h3>DONE"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<li>(.*?)</li>"
	for item in results:
            todos = (map(str, re.findall(patternCode, item, flags=0)))
	    if len(todos) > 0:
		TODO = "<ul><li>"+"</li><li>".join( todos )+"</li></ul>"
	    else:
		TODO = ""
	# Getting the done-list for the module
	pattern = r"DONE</h3>([\s\S]*)<h3>People"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<li>(.*?)</li>"
	for item in results:
            dones = (map(str, re.findall(patternCode, item, flags=0)))
	    if len(dones) > 0:
		DONE = "<ul><li>"+"</li><li>".join( dones )+"</li></ul>"
	    else:
		DONE = ""
	# Getting the peoplefor the module
	pattern = r"People</h3>([\s\S]*)<h2>License"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<li>(.*?)</li>"
	for item in results:
            peoples = (map(str, re.findall(patternCode, item, flags=0)))
	    if len(peoples) > 0:
		PEOPLE = "<ul><li>"+"</li><li>".join( peoples )+"</li></ul>"
	    else:
		PEOPLE = ""
	# Getting the progress	
	nbDone = len(dones)
	nbTodo = len(todos)
	if (nbTodo+nbDone)>0:
		PCProgress = (nbDone*100)/(nbTodo+nbDone)
	else:
		PCProgress = "NA"
	TableAvancement += "|"+ReadMe+"|"+TODO+"|"+DONE+"|"+PEOPLE+"|"+str(PCProgress)+"% |\n"

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

FinalDoc =  HeaderDocTxt+GraphModulesTxt+TableDocTxt+TableAvancement+AddInterfacesDocTxt+AddLicenseDocTxt

f = open("Readme.md","w+")
f.write(FinalDoc)
f.close()

# -------------------------
# Create the slider
# -------------------------

f = open("gh-pages/ppt.md","w+")
Presentation =  "% Habits\n% John Doe\n% March 22, 2005\r\n \r\n"+"\n# What do we do?\r\n \r\n"+HeaderDocTxt+" \n# Graping the modules\r\n \r\n"+GraphModulesTxt+" \n# Table Docs\r\n"+TableDocTxt+"\r\n# Progress\r\n \r\n"+TableAvancement
f.write(Presentation)
f.close()

# -------------------------
# Graph customised
# -------------------------

styles = {
    'graph': {
        'label': 'my mind',
	'layout':"neato",
	'fontsize':"26",
	'outputorder':'edgesfirst',
	#"overlap":"false",
        'rankdir': 'BT',
    }
}

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

GraphMyMind = digraph()

f = open("Worklog.md", 'r')
WorkLogMd=markdown.markdown( f.read() )
f.close()
# Getting the TODOs


pattern = r"<li>TODO: (.*?)</li>"
results = re.findall(pattern, WorkLogMd, flags=0) 
for item in results:
    GraphMyMind.node(item.replace(':', '-'), style="rounded,filled", fillcolor="yellow", penwidth="0")
    #GraphMyMind.edge("ToDo", item.replace(':', '-'))

# Getting the Innards of the Module
pattern = r"Graphing</h3>([\s\S]*)</ul>"
results = re.findall(pattern, WorkLogMd, flags=0) 
patternCode = r"<li>(.*?)</li>"
for item in results:
    Pairs= (map(str, re.findall(patternCode, item, flags=0)))
    for eachPair in Pairs:
	eachPair = eachPair.replace("<li>", "")
	eachPair = eachPair.replace("</li>", "")
	Couples = eachPair.split("-&gt;")		
	for single in Couples:
	    GraphMyMind.node(single, penwidth="0")
	# Add the edge		
	for k in range(len(Couples)-1):
	    GraphMyMind.edge(Couples[k], Couples[k+1])
	
GraphPath = 'include/GraphMyMind'
GraphMyMind = apply_styles(GraphMyMind, styles)

GraphMyMind.render(GraphPath)
Svg2Png(GraphPath)



f = open("Worklog.md", 'r')
ReadMehHtmlMarkdown=markdown.markdown( f.read() )
f.close()
#print ReadMehHtmlMarkdown

# Getting the Desc of the Module
pattern = r"<h4>(\d{4}-\d{2}-\d{2}.*)<\/h4>" # gets the titles
results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
titre = r"(.?*)<\/h4>" # gets the titles
resultstitre = re.findall(pattern, results[0], flags=0) 

ListePosts = []
for content in results:
	pair = []
	pattern2 = r""+content+"<\/h4>[\s\S]*?<h" # gets the titles
	results2 = "<h4>"+re.findall(pattern2, ReadMehHtmlMarkdown, flags=0)[0]+"4>"
	contenu = results2+"\n\n\n"
	tmp = re.findall(pattern, contenu, flags=0)[0]
	pair.append(tmp)
	pair.append(contenu)
	ListePosts.append(pair)
#print ListePosts


for item in ListePosts:
	titre = str(item[0])
	titre2=titre
	titre = titre.replace(" ", "-")
	adresse = "./gh-pages/_posts/"+titre+".html"
	#print adresse
	postcontent = str(item[1])
	entete = "--- <p>layout: post<p>title: "+titre2+"<p>---<p>"

	text_file = open(adresse, "w")
	text_file.write(entete+postcontent)
	text_file.close()



