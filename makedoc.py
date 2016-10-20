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

ExcludeDirs = ["include","retired","tools",".git","gh-pages","doc","gitbook"]
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
# Retired modules List
# -------------------------

ExcludeDirs = ["include","tools",".git","gh-pages"]
dirname = "./retired"
ListOfRetiredDirs = os.listdir(dirname)  
#print ListOfRetiredDirs
RetiredModulesDirs = []
# On itere
for f in ListOfRetiredDirs:
	if  os.path.isdir(f):
		RetiredModulesDirs.append(f)
# On retire les repertoires non modules


#print ListOfRetiredDirs

# -------------------------
# Files includes
# -------------------------

f = open("include/AddPitch.md",'r')
pitch = f.read()
f.close()

HeaderDoc = open("include/AddEchomods.md")
HeaderDocTxt = HeaderDoc.read()+"\n\n"
HeaderDoc.close()

AddInterfacesDoc = open("include/AddInterfaces.md")
AddInterfacesDocTxt = AddInterfacesDoc.read()+"\n\n"
AddInterfacesDoc.close()

AddLicenseDoc = open("include/AddLicense.md")
AddLicenseDocTxt = AddLicenseDoc.read()+"\n\n"
AddLicenseDoc.close()

f = open("include/AddPrinciples.md", 'r')
AddPrinciples = f.read()
f.close()

f = open("include/AddStructure.md", 'r')
AddStructure = f.read()
f.close()

f = open("include/AddStructureDetails.md", 'r')
AddStructureDetails = f.read()
f.close()
f = open("include/AdHocShoppingList.md", 'r')
AddShoppingList = f.read()
f.close()

# -------------------------
# Préparer un tableau de présentation
# -------------------------

TableModules = "# A recap of our modules \n\n\n"
TableModulesShort = "# A recap of our modules \n\n\n"

TableModules += "| ThumbnailImage | Name | In | Out |\n"
TableModules += "|------|-------|----|------|\n"
TableModulesShort += "| ThumbnailImage | Name | \n"
TableModulesShort += "|------|-------| \n"

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
	#print Desc
	print ReadMe
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

	TableModulesShort +=  "|<img src='https://github.com/kelu124/echomods/blob/master/"+ReadMe+"/viewme.png' align='center' width='150'>|**["+ReadMe+"](/"+ReadMe+"/Readme.md)**: "+Desc+"|\n"

TableDocTxt = TableModules+"\n\n"


# Saving it in a file
f = open("include/AddModulesSummary.md","w+")
f.write(TableDocTxt)
f.close()

# -------------------------
# Retired Modules Table
# -------------------------

TableRetiredModules = "# A recap of our retired modules \n\n\n"

TableRetiredModules += "| ThumbnailImage | Name | In | Out |\n"
TableRetiredModules += "|------|-------|----|------|\n"

for ReadMe in ListOfRetiredDirs:
	f = open("./retired/"+ReadMe+"/Readme.md", 'r')
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

	# Getting the Inputs of the Module
	pattern = r"Inputs</h3>([\s\S]*)<h3>Outputs"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<code>(.*?)</code>"
	Inputs = []
	for item in results:
	    Inputs = map(str, re.findall(patternCode, item, flags=0))
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
	if len(Outputs) > 0:
		outpoots = "<ul><li>"+"</li><li>".join( Outputs )+"</li></ul>"
	else:
		outpoots = ""


	TableRetiredModules += "|<img src='https://github.com/kelu124/echomods/blob/master/retired/"+ReadMe+"/viewme.png' align='center' width='150'>|**["+ReadMe+"](/retired/"+ReadMe+"/Readme.md)**: "+Desc+"|"+inpoots+"|"+outpoots+"|\n"

TableRetiredDocTxt = TableRetiredModules+"\n\n"

# -------------------------
# Créer le tableau d'avancement
# -------------------------

TableAvancement = "# Progress on building the modules \n\n\n"
TableAvancement += "## Module-wise \n\n\n"
TableAvancement += "Note that the 'BONUS!' represents something that _could_ be done, and does not count as a strict TODO.\n\n\n"
TableAvancement += "| Name of module | ToDo | Done |  Progress |\n"
TableAvancement += "|------|-------|----|-----|\n"

TODOsToShopping = ""

for ReadMe in ListOfDirs:
	f = open(ReadMe+"/Readme.md", 'r')
	ReadMehHtmlMarkdown=markdown.markdown( f.read() )
	f.close()
	#print ReadMehHtmlMarkdown
	# Getting the todo-list for the module
	pattern = r"Discussions</h2>([\s\S]*)<h3>DONE"
	results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
	patternCode = r"<li>(.*?)</li>"
	bonus = 0
 
	for item in results:
            todos = (map(str, re.findall(patternCode, item, flags=0)))
 
	    if len(todos) > 0:
		TODO = "<ul><li>"+"</li><li>".join( todos )+"</li></ul>"
		for todo in todos:
		    TODOsToShopping = TODOsToShopping+"* "+todo+" (in ["+ReadMe+"](/"+ReadMe+"/))\n"
	    else:
		TODO = ""
	    for itemtodo in todos:
		    if "BONUS!" in itemtodo:
	 		bonus = bonus + 1
        #print bonus
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
		PCProgress = ((nbDone)*100)/(nbTodo+nbDone-bonus)
	else:
		PCProgress = "NA"
	TableAvancement += "|"+ReadMe+"|"+TODO+"|"+DONE+"|"+str(PCProgress)+"% |\r\n"
TableAvancement +="\n\n"

TODOsToShopping = AddShoppingList+TODOsToShopping+"\n\n"

# Saving it in a file
f = open("include/AddTableAvancement.md","w+")
f.write(TableAvancement)
f.close()

# Saving it in a file
f = open("include/AddShoppingList.md","w+")
f.write(TODOsToShopping)
f.close()

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

GraphModulesTxt += "![Graph](/include/sets/basic.png) \n\n"

FinalDoc =  pitch+"\n\n"+HeaderDocTxt+AddStructure+GraphModulesTxt+TableDocTxt+TableAvancement+TODOsToShopping+TableRetiredDocTxt+AddInterfacesDocTxt+AddLicenseDocTxt

f = open("Readme.md","w+")
f.write(FinalDoc)
f.close()

# -------------------------
# Create the slider
# -------------------------

f = open("gh-pages/ppt.md","w+")
Presentation =  "% Habits\n% John Doe\n% March 22, 2005\r\n \r\n"+"\n# What do we do?\r\n \r\n"+HeaderDocTxt+" \n# Graphing the modules\r\n \r\n"+GraphModulesTxt+" \n# Table Docs\r\n"+TableDocTxt+"\r\n# Progress\r\n \r\n"+TableAvancement
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


# -------------------------
# Graphing the links
# -------------------------


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




# -------------------------
# Creating blog posts with the worklog
# -------------------------


f = open("Worklog.md", 'r')
WorkLogText = f.read() 
ReadMehHtmlMarkdown=markdown.markdown( WorkLogText )
f.close()

# Getting the Desc of the Module
pattern = r"<h4>(\d{4}-\d{2}-\d{2}.*)<\/h4>" # gets the titles
results = re.findall(pattern, ReadMehHtmlMarkdown, flags=0) 
titre = r"(.?*)<\/h4>" # gets the titles
resultstitre = re.findall(pattern, results[0], flags=0) 

print resultstitre

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


for item in ListePosts:
	titre = str(item[0])
	titre2=titre
	titre = titre.replace(" ", "-")
	adresse = "./gh-pages/_posts/"+titre+".html"
	postcontent = str(item[1])
	entete = "--- <p>layout: post<p>title: "+titre2+"<p>---<p>"
	# We save the post
	text_file = open(adresse, "w")
	text_file.write(entete+postcontent)
	text_file.close()

# -------------------------------------------------- #
#                    Gitbooking                      #
# -------------------------------------------------- #



ModulesChaptDeux = ["tobo","retroATL3","mogaba","goblin","tobo","toadkiller"]
ModulesChaptTrois = ["silent","cletus","croaker","doj","sleepy","oneeye"]

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

# -------------------------
# Gitbooking worklog
# -------------------------

MyLogs =  SearchString(WorkLogText,"-------","uControllers")

# Saving it in a file
f = open("include/AddMyLogs.md","w+")
f.write(MyLogs)
f.close()

# -------------------------
# Preface
# -------------------------

f = open("include/AddPitch.md",'r')
pitch = f.read()
f.close()


f = open("gitbook/README.md","w+")
f.write(AddRawHURL(pitch))
f.close()

# -------------------------
# Adding CHAPTER 1 : Histoire et principe des ultrasons
# -------------------------
f = open("include/AddEngineering.md", 'r')
AddEngineering = f.read()
f.close()


f = open("gitbook/Chapter1/engineering.md","w+")
f.write(IncludeImage(AddRawHURL(AddEngineering)))
f.close()


PrinciplesOfEchoes = ""
f = open("include/AddPrinciples.md", 'r')
PrinciplesOfEchoes += f.read()
f.close()

f = open("include/AddStructure.md", 'r')
PrinciplesOfEchoes += f.read()
f.close()
f = open("include/AddStructureDetails.md", 'r')
PrinciplesOfEchoes += f.read()
f.close()

f = open("gitbook/Chapter1/principles.md","w+")
f.write(IncludeImage(AddRawHURL(PrinciplesOfEchoes)))
f.close()


f = open("gitbook/Chapter1/modules.md","w+")
f.write(AddRawHURL(HeaderDocTxt))
f.close()

# list of modules

f = open("gitbook/Chapter1/listofmodules.md","w+")
f.write(IncludeImage(AddRawHURL(TableModulesShort)))
f.close()


# -------------------------
# Adding CHAPTER 2 : Basic kit
# -------------------------


for eachModule in ModulesChaptDeux:

	f = open(eachModule+"/Readme.md", 'r')
	ModuleDesc = f.read()
	f.close()

	f = open("gitbook/Chapter2/"+eachModule+".md","w+")
	f.write(AddRawHURL(GitBookizeModule(ModuleDesc,eachModule))+"\n\n")
	f.close()
	

	f = open("gitbook/Chapter2/"+eachModule+".md","w+")
	f.write(AddRawHURL(GitBookizeModule(ModuleDesc,eachModule))+"\n\n")
	f.close()

	# Resume pour Murgen
	MurgenSummary = "# The first iteration, Murgen\n\n"
	f = open("include/AddMurgenSummary.md", 'r')
	MurgenSummary = MurgenSummary+"\n\n"+AddOneLevel(f.read())
	f.close()
	f = open("./../murgen-dev-kit/Readme.md", 'r')
	MurgenSummary = MurgenSummary+"\n\n"+AddOneLevel(f.read())
	f.close()

	f = open("gitbook/devkit0.md","w+")
	f.write(AddRawMurgenURL(MurgenSummary)+"\n\n")
	f.close()

	# Resume pour le wireless
	WirelessSet = "# Wireless implementation of the modules\n\n"
	f = open("include/AddWireless.md", 'r')
	WirelessSet = WirelessSet+"\n\n"+AddOneLevel(f.read())
	f.close()
 	f = open("gitbook/devkit11.md","w+")
	f.write(AddRawHURL(WirelessSet)+"\n\n")
	f.close()


	# Resume technique de Murgen
	f = open("include/AddIntroMurgen.md", 'r')
	MurgenIntro = f.read()
	f.close()
	f = open("gitbook/Chapter2/murgensetup.md","w+")
	f.write(AddRawHURL(MurgenIntro)+"\n\n")
	f.close()

	# Adding zach's work
	Zach = ""
	f = open("./../murgen-dev-kit/worklog/Zach/Zach.md", 'r')
	Zach = f.read()
	f.close()

	f = open("./../murgen-dev-kit/worklog/Zach/2016-06-22.md", 'r')
	Zach = Zach+"\n\n"+AddOneLevel(f.read())
	f.close()

	f = open("./../murgen-dev-kit/worklog/Zach/2016-07-06.md", 'r')
	Zach = Zach+"\n\n"+AddOneLevel(f.read())
	f.close()

	f = open("gitbook/Chapter2/zach.md","w+")
	f.write(AddRawMurgenURL(Zach)+"\n\n")
	f.close()


	f = open("./../murgen-dev-kit/hardware/Readme.md", 'r')
	MurgenHard = f.read()
	f.close()
	f = open("gitbook/Chapter2/murgenhardware.md","w+")
	f.write(AddRawMurgenURL(MurgenHard)+"\n\n")
	f.close()


	f = open("./../murgen-dev-kit/software/Readme.md", 'r')
	MurgenSoft = f.read()
	f.close()
	f = open("gitbook/Chapter2/murgensoftware.md","w+")
	f.write(AddRawMurgenURL(MurgenSoft)+"\n\n")
	f.close()


# -------------------------
# Adding CHAPTER 3 : Notes and worklog
# -------------------------

for eachModule in ModulesChaptTrois:

	f = open(eachModule+"/Readme.md", 'r')
	ModuleDesc = f.read()
	f.close()

	f = open("gitbook/Chapter3/"+eachModule+".md","w+")
	f.write(AddRawHURL(GitBookizeModule(ModuleDesc,eachModule))+"\n\n")
	f.close()


# -------------------------
# Adding CHAPTER 4 : Notes and worklog
# -------------------------

walk_dir = "./"
DetailedLogs = []
notesLogs = []
for root, subdirs, files in os.walk(walk_dir):
  	for filename in files:
	    file_path = os.path.join(root, filename)
	    if (".md" in filename in filename and not "gh-pages" in file_path and not "gitbook" in file_path):
		if ("2016-" in filename):
			DetailedLogs.append(file_path)
		if ("notes_" in filename):
			notesLogs.append(file_path)

print DetailedLogs
print notesLogs

detailedLogText = "# Detailed logs of experiments\n\n"
for detailedlog in DetailedLogs:
	Adddetailedlog = open(detailedlog)
	detailedlog = detailedlog.split('/')[-1].replace(".md", "")
	detailedLogText += "# "+detailedlog+"\n\n"
	detailedLogText += AddTwoLevels(Adddetailedlog.read())+"\n\n"
	Adddetailedlog.close()

detailedNotesText = "# Detailed notes of research\n\n"
for detailednote in notesLogs:
	Adddetailednote = open(detailednote)
	detailednote = detailednote.split('/')[-1].replace(".md", "").replace("notes_", "Notes on ")
	detailedNotesText += "# "+detailednote+"\n\n"
	detailedNotesText += AddTwoLevels(Adddetailednote.read())+"\n\n"
	Adddetailednote.close()

# Saving it in a file

f = open("gitbook/Chapter4/README.md","w+")
f.write("# Introduction to the Chapter 4\n\n")
f.close()

f = open("gitbook/Chapter4/detailedlog.md","w+")
f.write(AddRawHURL(detailedLogText)+"\n\n")
f.close()

f = open("gitbook/Chapter4/detailednotes.md","w+")
f.write(AddRawHURL(detailedNotesText)+"\n\n")
f.close()

f = open("gitbook/Chapter4/rawworklog.md","w+")
f.write("# Raw worklog\n\n"+AddRawHURL(WorkLogLevel(MyLogs))+"\n\n")
f.close()

# Adding murgen's work

Sessions = []
ListOfMurgenSessions = ["Session_1.md","Session_2.md","Session_3.md","Session_4.md","Session_4b.md","Session_5.md","Session_6.md","Session_7.md","Session_8.md","Session_9_ATL.md",]

for SessionLog in ListOfMurgenSessions:
	f = open("./../murgen-dev-kit/worklog/"+SessionLog, 'r')
	Sessions.append(f.read())
	f.close()
 
for i in range(len(Sessions)):
	Sessions[i] = AddRawMurgenURL(Sessions[i])

for i in range(len(Sessions)):
	f = open("gitbook/Chapter4/"+ListOfMurgenSessions[i], "w+")
	f.write(Sessions[i]+"\n\n")
	f.close()

WikiNotes = ""
f = open("./../murgen-dev-kit/worklog/notes.md", 'r')
WikiNotes = AddRawMurgenURL(f.read())
f.close()

f = open("gitbook/Chapter4/murgenworklog.md","w+")
f.write(WikiNotes)
f.close()


# -------------------------
# Adding CHAPTER 5 : Data 
# -------------------------

f = open("include/AddFormatRules.md", 'r')
DataFormat = f.read()
f.close()

f = open("gitbook/Chapter5/dataformat.md","w+")
f.write("# DataFormat \n\n"+AddRawHURL(DataFormat)+"\n\n")
f.close()

f = open("./../murgen-dev-kit/software/examples/Readme.md", 'r')
Examples = f.read()
f.close()

Examples = Examples.split("# ")
TableDataExamples = "# "+Examples[-1]
f = open("gitbook/Chapter5/images.md","w+")
f.write("# Still images from murgen \n\n"+TableDataExamples+"\n\n")
f.close()

f = open("croaker/data/examples/Readme.md", 'r')
Examples_croaker = f.read()
f.close()

f = open("gitbook/Chapter5/croaker_data.md","w+")
f.write("# Images acquired using Croaker \n\n"+AddRawHURL(AddOneLevel(Examples_croaker))+"\n\n")
f.close()


Loops = ""
f = open("include/20160814/2016-08-14-HackingAUltrasoundProbe.md", 'r')
Loops += f.read() + "\n\n"
f.close()
f = open("include/20160822/2016-08-22-Fantom.md", 'r')
Loops += f.read() + "\n\n"
f.close()


f = open("gitbook/Chapter5/loops.md","w+")
f.write("# Adding videos \n\n There are two loops saved so far. \n\n"+AddRawHURL(AddOneLevel(Loops))+"\n\n")
f.close()



# -------------------------
# Adding CHAPTER 6 : Biblio 
# -------------------------


f = open("include/Bibliography.md", 'r')
articles = f.read()
f.close()

f = open("gitbook/Chapter6/articles.md","w+")
f.write("# Bibliography \n\n"+AddRawHURL(articles)+"\n\n")
f.close()

f = open("./../murgen-dev-kit/worklog/bibliographie.md", 'r')
electronics = f.read()
f.close()

electronics = electronics.replace("# Our setup\n","")


f = open("gitbook/Chapter6/components.md","w+")
f.write("# Our choice of electronics \n\n"+electronics+"\n\n")
f.close()


f = open("gitbook/Chapter6/interfaces.md","w+")
f.write("# List of modules Interfaces \n\n"+AddRawHURL(AddInterfacesDocTxt)+"\n\n")
f.close()

f = open("include/AddDocProcess.md", 'r')
AddDocProcess = f.read()
f.close()

f = open("gitbook/Chapter6/documentationprocess.md","w+")
f.write("# Automating documentation \n\n"+AddRawHURL(AddDocProcess)+"\n\n")
f.close()

# -------------------------
# Adding CHAPTER 7 : Contributing
# -------------------------

f = open("gitbook/Chapter7/progress.md","w+")
f.write("# The table of progress \n\n"+TableAvancement+"\n\n")
f.close()

f = open("gitbook/Chapter7/shoppingList.md","w+")
f.write(TODOsToShopping+"\n\n")
f.close()

f = open("gitbook/Chapter7/license.md","w+")
f.write(AddLicenseDocTxt+"\n\n")
f.close()



