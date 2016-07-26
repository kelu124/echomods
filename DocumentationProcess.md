% Documentation Process
% kelu124
% June 27, 2016
 

# What is this presentation?

I have been working on a open-source hardware project and documentation is key. A question remains. 

___I'm lazy, how do I make the documentation process efficient, and as system-independant as possible?___

# Inputs

I'm working only with a couple of _Readmes_:

* One per module (one per folder)
* One __worklog.md__ file

## Other inputs

## Other inputs 2

# A ReadMe per folder

We have identified a way to build a module documentation, following guidelines:

* A __Readme.me__ to get all information
* A __viewme.png__ for a representation of the module
* A __source__ and a __build__ folder.

# ReadMe's structures

* `# Module: XX`
* `# Name`
* `# Title`
* `# Description`
* `# IOs`
* `# Key Components`
* `# License`

# Worklog

* Several _raw notes_ parts, then..
* __Notes__
* `Worklog -- Starting April 5th 2016`
* `-------`
* `### 2016-04-05 Title1`
* `### 2016-04-06 Title2 ...`
* __Mindmapping__
* `ConceptZ->ConceptA`

# Using Worklog

To generate the blog, and to generate a mindmap of concepts.

It also highlights the _TODOs_

# Generating the blog

All dated elements generate individual posts on the corresponding github page, here [http://kelu124.github.io/echomods/](http://kelu124.github.io/echomods/).

# Mindmap {data-background="https://raw.githubusercontent.com/kelu124/echomods/master/include/GraphMyMind.png"}

Worklog generates a [mindmap](https://github.com/kelu124/echomods/blob/master/include/GraphMyMind.png) of the concepts I have in mind at the moment.


# Using the Readme's

* The Readme's are used to generate the overall graph of links between the modules
* The Readmes create the table of modules at __/Readme.md__
* They also update the table of progress
* Last but not least, they create the graph representing how the modules work, internally, connecting the interfaces

# Graph of links  {data-transition="zoom" data-background="https://raw.githubusercontent.com/kelu124/echomods/master/include/ModulesGraph.png"}


# Table: modules {data-transition="slide-in fade-out"}

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/images/table_modules.png)

# Table: progress {data-transition="fade-in slide-out"}

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/images/table_progress.png)

# Block diagram  {data-transition="fade-in slide-out"}



![](https://raw.githubusercontent.com/kelu124/echomods/master/tobo/source/blocks.png)


# Tools used

* __Python and bash__ for the scripts
* __Graphviz__ to generate graphs
* __Pandoc__ to convert documentation
* __gh-pages / Jekyll__ for the site
* __Reveal.js__ for the presentations

# Conclusion

An efficient (err, lazy) way of documenting. Only one place to edit information, will be updated everywhere, even in this presentation!

# Pending Work

* Publishing automatically a presentation of the modules.. will need some inputs from the /include/ folder =)

# Q&A

Or ping me @kelu124 / kelu124@gmail.com !
