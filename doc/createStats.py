from urllib2 import urlopen
import bs4 as BeautifulSoup
import os
from datetime import datetime, date, time

def insert(originalfile,string):
    with open(originalfile,'r') as f:
        with open('newfile.txt','w') as f2: 
            f2.write(string)
            f2.write(f.read())
    os.rename('newfile.txt',originalfile)
    
def th(number):
    if "k" in number:
        value = int(float(number[:-1])*1000)
    else:
        value = int(number)
    return value

ResString = "### Some stats\n\n"


names= ["HSDK","Murgen","ADC cape"]
url = ["https://hackaday.io/project/10899","https://hackaday.io/project/9281","https://hackaday.io/project/20455"]

for k in range(len(names)):
    html = urlopen(url[k]).read()
    soup = BeautifulSoup.BeautifulSoup(html, "lxml")
    t = th(soup.find("span", {"title": "View Count"}).text)
    u = th(soup.find("span", {"title": "Followers"}).text)
    v = th(soup.find("span", {"title": "Likes"}).text)
    ResString += "* __"+names[k]+"__: "+str(t)+ " views, "+str(u)+ " followers, "+str(v)+ " likes\n"

urlJOH = "https://openhardware.metajnl.com/articles/10.5334/joh.2/metrics/#views"
html = urlopen(urlJOH).read()
soup = BeautifulSoup.BeautifulSoup(html, "lxml")
t = th(soup.find("li", {"class": "metrics-slab views"}).text.strip().split("\n")[0])
u = th(soup.find("li", {"class": "metrics-slab downloads"}).text.strip().split("\n")[0])
ResString += "* __JOH publication__: "+str(t)+" views and "+str(u)+" downloads.\n\n"



insert("../include/AddStatsFull.md",ResString+"--- "+str(datetime.now())   +"\n\n")
text_file = open("../include/AddStats.md", "w")
text_file.write(ResString)
text_file.close()
