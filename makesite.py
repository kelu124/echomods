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
print ListePosts

for item in ListePosts:
	titre = str(item[0])
	adresse = "./gh-pages/_posts/"+titre+".html"
	print adresse
	postcontent = str(item[1])
	text_file = open(adresse, "w")

	text_file.write(postcontent)
	
	text_file.close()
	

