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
from doc.mkdoc import *
 

GraphModules = digraph()


# -------------------------
# Obtenir la liste des modules
# -------------------------
MDFiles = GetGeneratedFiles("./")

OpenWrite("* "+"\n* ".join(MDFiles[0]),"include/GeneratedFiles.md")
OpenWrite("* "+"\n* ".join(MDFiles[1]),"include/ManualFiles.md")


ListOfDirs = GetListofModules("./")
for eachInput in ListOfDirs:
	GraphModules.node(eachInput, style="filled", fillcolor="blue", shape="box",fontsize="22")
print ListOfDirs

# -------------------------
# Retired modules List
# -------------------------

ListOfRetiredDirs = GetListofModules("./retired")
print ListOfRetiredDirs

# -------------------------
# Files includes
# -------------------------

pitch = getText("include/AddPitch.md")
HeaderDocTxt = getText("include/AddEchomods.md")+getText("include/sets/KitCosts.md")
AddInterfacesDocTxt= getText("include/AddInterfaces.md")
AddLicenseDocTxt = getText("include/AddLicense.md")
AddPrinciples = getText("include/AddPrinciples.md")
AddStructure = getText("include/AddStructure.md")
AddStructureDetails = getText("include/AddStructureDetails.md")
AddShoppingList = getText("include/AdHocShoppingList.md")

# -------------------------
# Préparer un tableau de présentation
# -------------------------

TableModules = "# A recap of our modules \n\n\n"
TableModulesShort = "# A recap of our modules \n\n\n"

TableModules += "| ThumbnailImage | Name | In | Out |\n|------|-------|----|------|\n"
TableModulesShort += "| ThumbnailImage | Name | \n|------|-------| \n"

for ReadMe in ListOfDirs:
	[soup,ReadMehHtmlMarkdown] = returnSoup(ReadMe+"/Readme.md")

	#print getParam(ReadMe,"ds")
	ModuleDesc = returnHList(soup,"h2","Description")
	if len(GetParams(ModuleDesc)) > 0:
		Parameter = "__[MDL "+ReadMe+ "]__ "+GreenMark+" Metadata ("
		Parameter += ", ".join(GetParams(ModuleDesc))+")"
		log.append(Parameter+"\n")
	else:
		log.append("__[MDL "+ReadMe+ "]__ "+RedMark+"Metadata missing"+"\n")

	[soup,ReadMehHtmlMarkdown] = returnSoup(ReadMe+"/Readme.md")
	# OK - Check real name
	ModuleNomenclature = getHs(soup,"h2","Name")
	if len(ModuleNomenclature)>0: 
	    NameCheck = "__[MDL "+ReadMe+ "]__ "+GreenMark+" 01. Real name found: "+ModuleNomenclature.find_next("code").text+"\n"
	    log.append(NameCheck)
	if len(NameCheck)==0:
	    log.append("__[MDL "+ReadMe+ "]__ "+RedMark+" 01. No Real name found "+"\n")
 
	[soup,ReadMehHtmlMarkdown] = returnSoup(ReadMe+"/Readme.md")
	# Getting the Desc of the Module
	ModuleDesc = getHs(soup,"h3","What is it supposed to do?")
	Desc = ModuleDesc.find_next("p").text

	[soup,ReadMehHtmlMarkdown] = returnSoup(ReadMe+"/Readme.md")
	# OK - Getting the Innards of the Module // inside the block diagram
	GraphThisModule = digraph()
	Paires =  returnHList(soup,"h3","block diagram")
   	if (len(Paires) > 0):
		GraphModule(Paires,GraphThisModule,ReadMe)
		log.append("__[MDL "+ReadMe+ "]__ "+GreenMark+" 01. Block diagram OK"+"\n")
	else:
	    	log.append("__[MDL "+ReadMe+ "]__ "+RedMark+" 01. No block diagram section "+"\n")

	# OK - Getting the Inputs of the Module
	ItemList =  returnHList(soup,"h3","Inputs")
	inpoots = ""
	Module = []
 	for OneIO in ItemList:
		codes = getCode(OneIO)
		if len(codes) > 0:
		    for EachIO in codes:
			Module.append(EachIO)
	if len(Module)>0:
	    inpoots = "<ul>"
	    for item in Module:
		inpoots += "<li>"+item+"</li>"
		if "ITF-m" not in item:
		    GraphModules.node(item, style="rounded,filled", fillcolor="yellow")
		else:
		    GraphModules.node(item, style="rounded,filled", fillcolor="green")		
		GraphModules.edge(item, ReadMe, splines="line", nodesep="1")
	    inpoots += "</ul>"
	    log.append("__[MDL "+ReadMe+ "]__ "+GreenMark+" "+str(len(ItemList))+" input(s)"+"\n")
	if len(ItemList)==0:
	    log.append("__[MDL "+ReadMe+ "]__ "+RedMark+" 02. No inputs "+"\n")


	# OK - Getting the Outputs of the Module
	ItemList =  returnHList(soup,"h3","Outputs")
	Module = []
	outpoots = ""
 	for OneIO in ItemList:
		codes = getCode(OneIO)
		if len(codes) > 0:
		    for EachIO in codes:
			Module.append(EachIO)
	if len(Module)>0:
	    outpoots = "<ul>"
	    for item in Module:
		outpoots += "<li>"+item+"</li>"
		if "ITF-m" not in item:
		    GraphModules.node(item, style="rounded,filled", fillcolor="yellow")
		else:
		    GraphModules.node(item, style="rounded,filled", fillcolor="green")		
		GraphModules.edge(item, ReadMe, splines="line", nodesep="1")
	    outpoots += "</ul>"
	    log.append("__[MDL "+ReadMe+ "]__ "+GreenMark+" "+str(len(ItemList))+" output(s)"+"\n")
	if len(ItemList)==0:
	    log.append("__[MDL "+ReadMe+ "]__ "+RedMark+" 02. No outputs "+"\n")


	TableModules += "|<img src='https://github.com/kelu124/echomods/blob/master/"+ReadMe+"/viewme.png' align='center' width='150'>|**["+ReadMe+"](/"+ReadMe+"/Readme.md)**: "+Desc+"|"+inpoots+"|"+outpoots+"|\n"

	TableModulesShort +=  "|<img src='https://github.com/kelu124/echomods/blob/master/"+ReadMe+"/viewme.png' align='center' width='150'>|**["+ReadMe+"](/"+ReadMe+"/Readme.md)**: "+Desc+"|\n"


# Saving it in a file
OpenWrite(TableModules+"\n\n","include/AddModulesSummary.md")


# -------------------------
# Retired Modules Table
# -------------------------

TableRetiredModules = "# A recap of our retired modules \n\n\n"
TableRetiredModules += "| ThumbnailImage | Name | In | Out |\n"
TableRetiredModules += "|------|-------|----|------|\n"

for ReadMe in ListOfRetiredDirs:

	[soup,ReadMehHtmlMarkdown] = returnSoup("./retired/"+ReadMe+"/Readme.md")

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
OpenWrite(TableAvancement,"include/AddTableAvancement.md")

# Saving it in a file
OpenWrite(TODOsToShopping,"include/AddShoppingList.md")

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

FinalDoc =  pitch+"\n\n"+HeaderDocTxt+AddStructure+GraphModulesTxt+TableModules+TableAvancement+TODOsToShopping+TableRetiredDocTxt+AddInterfacesDocTxt+AddLicenseDocTxt

OpenWrite(FinalDoc,"Readme.md")

# -------------------------
# Create the slider
# -------------------------

f = open("gh-pages/ppt.md","w+")
Presentation =  "% Habits\n% John Doe\n% March 22, 2005\r\n \r\n"+"\n# What do we do?\r\n \r\n"+HeaderDocTxt+" \n# Graphing the modules\r\n \r\n"+GraphModulesTxt+" \n# Table Docs\r\n"+TableModules+"\r\n# Progress\r\n \r\n"+TableAvancement
f.write(Presentation)
f.close()


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

# Getting the title of the article
pattern = r"<h4>(\d{4}-\d{2}-\d{2}.*)<\/h4>" # gets the contents
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

log.append("__[WEB Blog]__ "+str(len(ListePosts))+" posts added"+"\n")


# -------------------------------------------------- #
#                    Gitbooking                      #
# -------------------------------------------------- #

# -------------------------
# Gitbooking worklog
# -------------------------

MyLogs =  SearchString(WorkLogText,"-------","uControllers")
OpenWrite(MyLogs,"include/AddMyLogs.md")


# -------------------------
# Preface
# -------------------------

Preface = AddOneLevel(getText("include/AddPitch.md")) + "\n" + getText("include/AddEchomods.md") 
OpenWrite(Preface,"gitbook/README.md")


# -------------------------
# Adding CHAPTER 1 : Histoire et principe des ultrasons
# -------------------------

AddEngineering = getText("include/AddEngineering.md")
OpenWrite(IncludeImage(AddRawHURL(AddEngineering)),"gitbook/Chapter1/engineering.md")

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

OpenWrite(IncludeImage(AddRawHURL(PrinciplesOfEchoes)),"gitbook/Chapter1/principles.md")
OpenWrite(AddRawHURL(HeaderDocTxt),"gitbook/Chapter1/modules.md")

# list of modules
OpenWrite(IncludeImage(AddRawHURL(TableModulesShort)),"gitbook/Chapter1/listofmodules.md")


# -------------------------
# Adding CHAPTER 2 : Basic kit
# -------------------------

for eachModule in ModulesChaptDeux:
	ModuleDesc = getText(eachModule+"/Readme.md")
	OpenWrite(AddRawHURL(GitBookizeModule(ModuleDesc,eachModule))+"\n\n","gitbook/Chapter2/"+eachModule+".md")

# Resume pour Murgen
MurgenSummary = "# The first iteration, Murgen\n\n"
f = open("include/AddMurgenSummary.md", 'r')
MurgenSummary = MurgenSummary+"\n\n"+AddOneLevel(f.read())
f.close()
f = open("./../murgen-dev-kit/Readme.md", 'r')
MurgenSummary = MurgenSummary+"\n\n"+AddOneLevel(f.read())
f.close()
OpenWrite(AddRawMurgenURL(MurgenSummary)+"\n\n","gitbook/devkit0.md")

# Resume pour le wireless


WirelessSet = "# Wireless implementation of the modules\n\n"+"\n\n"+AddOneLevel(getText("include/AddWireless.md"))
OpenWrite(AddRawHURL(WirelessSet)+"\n\n","gitbook/devkit11.md")

# Resume technique de Murgen
OpenWrite(AddRawHURL(getText("include/AddIntroMurgen.md"))+"\n\n","gitbook/Chapter2/murgensetup.md")

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


OpenWrite(AddRawMurgenURL(Zach)+"\n\n","gitbook/Chapter2/zach.md")
OpenWrite(AddRawMurgenURL(getText("./../murgen-dev-kit/hardware/Readme.md"))+"\n\n","gitbook/Chapter2/murgenhardware.md")
OpenWrite(AddRawMurgenURL(getText("./../murgen-dev-kit/software/Readme.md"))+"\n\n","gitbook/Chapter2/murgensoftware.md")



# -------------------------
# Adding CHAPTER 3 : Notes and worklog
# -------------------------

for eachModule in ModulesChaptTrois:
	ModuleDesc = getText(eachModule+"/Readme.md")
	OpenWrite(AddRawHURL(GitBookizeModule(ModuleDesc,eachModule))+"\n\n","gitbook/Chapter3/"+eachModule+".md")

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
OpenWrite("# Introduction to the Chapter 4\n\n","gitbook/Chapter4/README.md")
OpenWrite(AddRawHURL(detailedLogText)+"\n\n","gitbook/Chapter4/detailedlog.md")
OpenWrite(AddRawHURL(detailedNotesText)+"\n\n","gitbook/Chapter4/detailednotes.md")
OpenWrite("# Raw worklog\n\n"+AddRawHURL(WorkLogLevel(MyLogs))+"\n\n","gitbook/Chapter4/rawworklog.md")


# Adding murgen's work

Sessions = []
for SessionLog in ListOfMurgenSessions:
	f = open("./../murgen-dev-kit/worklog/"+SessionLog, 'r')
	Sessions.append(f.read())
	f.close()
for i in range(len(Sessions)):
	OpenWrite(AddRawMurgenURL(Sessions[i])+"\n\n","gitbook/Chapter4/"+ListOfMurgenSessions[i])
# And the log
CopyGitBookMurgenFile("./../murgen-dev-kit/worklog/notes.md","gitbook/Chapter4/murgenworklog.md")




# -------------------------
# Adding CHAPTER 5 : Data 
# -------------------------


DataFormat = getText("include/AddFormatRules.md")
OpenWrite("# DataFormat \n\n"+AddRawHURL(DataFormat)+"\n\n","gitbook/Chapter5/dataformat.md")

Examples = getText("./../murgen-dev-kit/software/examples/Readme.md").split("# ")
TableDataExamples = "# "+Examples[-1]
OpenWrite("# Still images from murgen \n\n"+TableDataExamples+"\n\n","gitbook/Chapter5/images.md")

Examples_croaker=getText("croaker/data/examples/Readme.md")
OpenWrite("# Images acquired using Croaker \n\n"+AddRawHURL(AddOneLevel(Examples_croaker))+"\n\n","gitbook/Chapter5/croaker_data.md")

Loops = ""
f = open("include/20160814/2016-08-14-HackingAUltrasoundProbe.md", 'r')
Loops += f.read() + "\n\n"
f.close()
f = open("include/20160822/2016-08-22-Fantom.md", 'r')
Loops += f.read() + "\n\n"
f.close()

OpenWrite("# Adding videos \n\n There are two loops saved so far. \n\n"+AddRawHURL(AddOneLevel(Loops))+"\n\n","gitbook/Chapter5/loops.md")

# -------------------------
# Adding CHAPTER 6 : Biblio 
# -------------------------

articles=getText("include/Bibliography.md")
OpenWrite("# Bibliography \n\n"+AddRawHURL(articles)+"\n\n","gitbook/Chapter6/articles.md")

electronics = getText("./../murgen-dev-kit/worklog/bibliographie.md").replace("# Our setup\n","")
OpenWrite("# Our choice of electronics \n\n"+electronics+"\n\n","gitbook/Chapter6/components.md")

OpenWrite("# List of modules Interfaces \n\n"+AddRawHURL(AddInterfacesDocTxt)+"\n\n","gitbook/Chapter6/interfaces.md")

AddDocProcess =getText("include/AddDocProcess.md")
OpenWrite("# Automating documentation \n\n"+AddRawHURL(AddDocProcess)+"\n\n","gitbook/Chapter6/documentationprocess.md")

CopyGitBookFile("include/biblio/Readme.md","gitbook/Chapter6/academicbiblio.md")
# -------------------------
# Adding CHAPTER 7 : Contributing
# -------------------------

OpenWrite("# The table of progress \n\n"+TableAvancement+"\n\n","gitbook/Chapter7/progress.md")
OpenWrite(TODOsToShopping+"\n\n","gitbook/Chapter7/shoppingList.md")
OpenWrite(AddLicenseDocTxt+"\n\n","gitbook/Chapter7/license.md")
CopyGitBookFile("CLA.md","gitbook/CLA.md")

# -------------------------
# Saving the compilation log
# -------------------------

ResultKits = CreateKits("./include/","./")
log = log+ResultKits

# -------------------------
# Saving the compilation log
# -------------------------

log.sort()
OpenWrite("\n".join( log ),"doc/log.md")

