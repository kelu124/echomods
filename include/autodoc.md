# Process

## Principle

Automating most of the documentation	

## Structure

* Probes
  * Experiments
  * Pictures
  * Name of probe is an extension of the modules 
* __Pictures__ can store information that can be reused. This info can contain
  * Author
  * Experiment
  * Modules
  * Description
  * Type of picture
* __Contributors__ have a dedicated folder
  * Name
  * Pictures
  * Experiments
* __Experiments__

## Functions

* _*.tpl_ type -> 
* _@todo_ lines in a text are parsed and set into a todo list
* All ``ExperimentNumber`` go into the experiment folder
  * All `Experiment folder` having Readme's get into the descripton of the readme
* Probes are listed as modules, as in the list defined

# Gitbook

## What goes inside ?

* Gitbook __SUMMARY.md__ is created from the __toc.md__ file
  * List of experiments gets included in the Summary
  * List of probes gets included in the Summary
  * List of python Jupyter notebooks 

## Inputting Jupyter Notebook's into the Gitbook

The trick is to convert all Notebooks to MD files, and have those included in the summary of the GitBook. [The script is here.](/makeipynb.sh)

# Contributors

Contributors who have shared something are added the /include/community/ folder. 

It also enables the creation of the map of the place of contributors.


# Logs created

* Scripts used:
  * [Python makedoc file](/makedoc.py)
  * [Support functions for the makedoc](/doc/mkdoc.py)

* Logs created : they are useful to know what is working good or not
  * [Log of important errors](/doc/urgent.md)
  * [List of documentation compilation warning](/doc/log.md)

All files properties are kept in this JSON:
* [Doc JSON](/include/doc.json)

# Experiments descriptions

* [Description of experiments](/include/experiments/all.md): this is where the experiments short names are listed. It can help identify what experiment is what.
* [Description of probes](/include/probes/define.md): likewise, codenames of the probes are set here, and corresponding resources within the repo are listed.

# Stats from articles and hackaday are added to the stats

* [Automated Stats](/include/AddStats.md)

# Other includes 

* [Different todos from the documentation](/include/AddShoppingList.md)
* [Manufacturing MF](/include/MF.md)
* [Chapters introductions](/include/AddChaptersIntro.md) 
* [Press review](/include/AddPressReview.md)
* [Pitch](/include/AddPitch.md)
* [List of all experiments](/include/AllExpes.md) 
* [Finance](/include/Finance.md)
* [JSON of the documentation](/include/doc.json)
* [probes list](/include/probes/auto) 
* [list of experiments](/include/experiments) 
* [all references](/include/biblio/bib/AllRefs.md)
* [Automated Stats](/include/AddStats.md)


