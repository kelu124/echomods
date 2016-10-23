% Documentation Process, updated
% kelu124
% August 25, 2016
 
#### Open-source documentation

* assists people getting started with it
* identifies the problem it's solving
* gives a high level impression of the feel or focus of the project and its solution
* helps the project developer(s) validate that the product they're writing makes sense
* shows that the developer(s) care enough and will actively maintain or steward community maintenance over time
* plenty more.

#### What is this presentation?

I have been working on a open-source hardware project and documentation is key. A question remains. 

___I'm lazy, how do I make the documentation process efficient, and as system-independant as possible?___

#### What do I want to automatize?

* A __[github documentation](http://github.com/kelu124/echomods/)__
* A __Jekyll blog__  [on github-pages](http://kelu124.github.io/echomods/).
* All-purpose __presentations__ such as this one
* A __gitbook__ that can be [read here](https://kelu124.gitbooks.io/echomods/content/)
* Simple vizualization of the work progress
* _All of this can be pushed directly to a __wiki__ as well_

#### Inputs (1/2)

I want to:

* not repeat myself
* write once and only once each block of info
* use the "modules" concepts : _seeds_ of information
* use only text

Conclusion: creation of [markdown "blocks"](https://github.com/kelu124/echomods/blob/master/include/ManualFiles.md) which will feed all the generated docs (see a list [here](https://github.com/kelu124/echomods/blob/master/include/GeneratedFiles.md)).



#### Inputs (2/2)

The script is working only with a couple of files:

* One __worklog.md__ file
* One __ReadMe__ per module 
* Some Worklog files, dated __.md__ files.
* Some specific content files, in __/include/Add*.md__

#### Using the files

* These files are used to generate the overall documentation
* The files create the table of modules at __/Readme.md__
* They update the __gitbook__
* They also update the __table of progress__
* They create the graph of links between the modules
* Last but not least, they create __the graphs__ representing how the modules work, internally, connecting the interfaces

#### Using Worklog

The worklog is used to generate the gitbook, the blog, and to generate a mindmap of concepts.

It also highlights the _TODOs_ in the mindmap.



#### Graph of links  {data-transition="zoom" data-background="https://raw.githubusercontent.com/kelu124/echomods/master/include/ModulesGraph.png"}

#### Gitbook {data-transition="slide-in fade-out"}

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/images/table_gitbook.png)

#### Table: modules {data-transition="slide-in fade-out"}

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/images/table_modules.png)

#### Table: progress {data-transition="fade-in slide-out"}

![](https://raw.githubusercontent.com/kelu124/echomods/master/include/images/table_progress.png)

#### Block diagram  {data-transition="fade-in slide-out"}

![](https://raw.githubusercontent.com/kelu124/echomods/master/tobo/source/blocks.png)


#### Toolchain

* __markdown / github__ to store all the docs
* __gitbook__ to publish a general documentation
* __gh-pages / Jekyll__ for the static site
* __python / Graphviz__ to generate documentation / graphs
* __Pandoc__ to convert documentation between formats
* __pywikibot__ to publish to a wiki
* __Reveal.js__ for the presentations

#### Conclusion

An efficient (err, lazy) way of documenting. Only one place to edit information, will be updated everywhere, even in this presentation! The outputs are ever-updated documents, such as :

* A __github documentation__
* A __Jekyll blog__ on github-pages
* All-purpose __presentations__
* A __gitbook__

The documentation compiler  becomes a [debugger](https://github.com/kelu124/echomods/blob/master/doc/log.md)

#### TODO

Experience

* Work on the user experience
* What flow to capture the visitor, and guide him?
* --> Need a story



#### Q&A

Ping  @kelu124 / kelu124@gmail.com 
