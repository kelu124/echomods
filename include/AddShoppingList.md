## Shopping list

Here's a couple of things we're working on, for which you could help as well.

* Boosting the [6Msps croaker](/retired/croaker/) acquisition (see Wayne?) to the full 6Msps 

### Todos from Modules
* None (in [wirephantom](/wirephantom/))
* See the <a href="/matty/nextsteps.md">next steps</a> (in [matty](/matty/))
* Having it work with a <a href="/retroATL3/">retroATL3</a> (in [matty](/matty/))
* Test Goblin v2 (in [goblin](/goblin/))
* Review a bipolar design (originally alt.tbo -- but double the components and hence the price) (in [lite.tbo](/lite.tbo/))
* Preliminary testing (in [lite.tbo](/lite.tbo/))
* Ivan for the TC6320TG (in [lite.tbo](/lite.tbo/))
* The second iteration of the HV-Pulser of the echOmods (in [lite.tbo](/lite.tbo/))
* Setup? Soon a quickstart? (in [lite.tbo](/lite.tbo/))
* version: V0.1 (in [lite.tbo](/lite.tbo/))
* cost:120$ (in [lite.tbo](/lite.tbo/))
* sourcing:Tindie (in [lite.tbo](/lite.tbo/))
* date: 15/04/2018 (in [lite.tbo](/lite.tbo/))
* technology: Module-compatible, Homemade PCB, ICs based on <code>TC6320TG</code> and <code>NMT0572SC</code> (in [lite.tbo](/lite.tbo/))
* language: Altium (in [lite.tbo](/lite.tbo/))
* author: Kelu124 (in [lite.tbo](/lite.tbo/))
* <code>ITF-1_GND</code> (in [lite.tbo](/lite.tbo/))
* <code>ITF-2_VDD_5V</code> (in [lite.tbo](/lite.tbo/))
* <code>ITF-9_Pon</code>  (in [lite.tbo](/lite.tbo/))
* <code>ITF-10_Poff</code>  (in [lite.tbo](/lite.tbo/))
* <code>ITF-19_3.3V</code> (in [lite.tbo](/lite.tbo/))
* <code>ITF-mET_Transducer</code> : signal coming back  (in [lite.tbo](/lite.tbo/))
* <code>ITF-18_Raw</code>  : for the signal coming from the transducer (in [lite.tbo](/lite.tbo/))
* <code>ITF-mET_SMA</code> : for the signal coming out to the signal processing (if through SMA) (in [lite.tbo](/lite.tbo/))
* <code>ITF-mET_Transducer</code> : for the signal coming out of the pulser (if through SMA) (in [lite.tbo](/lite.tbo/))
* <code>TC6320TG</code> (in [lite.tbo](/lite.tbo/))
* <code>NMT0572SC</code> (in [lite.tbo](/lite.tbo/))
* <code>Pulse-P</code>-&gt;<code>TC6320TG</code> (in [lite.tbo](/lite.tbo/))
* <code>Pulse-N</code>-&gt;<code>TC6320TG</code> (in [lite.tbo](/lite.tbo/))
* <code>Damper</code>-&gt;<code>TC6320TG</code> (in [lite.tbo](/lite.tbo/))
* <code>NMT0572SC</code>-&gt;<code>HV-N</code>-&gt;<code>TC6320TG</code> (in [lite.tbo](/lite.tbo/))
* <code>NMT0572SC</code>-&gt;<code>HV-P</code>-&gt;<code>TC6320TG</code>-&gt;<code>ITF-mET_Transducer</code> (in [lite.tbo](/lite.tbo/))
* <code>ITF-mET_Transducer</code>-&gt;<code>ITF-mET_SMA</code> (in [lite.tbo](/lite.tbo/))
* <code>ITF-mET_Transducer</code>-&gt;<code>ITF-18_Raw</code> (in [lite.tbo](/lite.tbo/))
* Cheaper, more robust than <a href="/retired/tobo/">tobo</a> (in [lite.tbo](/lite.tbo/))
* Less issues with the MD0100 (in [lite.tbo](/lite.tbo/))
* As of today (20180305), the damper still lacks (in [lite.tbo](/lite.tbo/))
* Needed to get a couple of 10's of ns wide square pulses, both in the positive and negative. (in [lite.tbo](/lite.tbo/))
* Control of pulses must be through 3.3 or 5V tolerant logic (in [lite.tbo](/lite.tbo/))
* Pulses height must be selectable (say with a jumper?) for ~20V, 40V, 80V (for positive pulses). (in [lite.tbo](/lite.tbo/))
* Only power supply available is 5V (in [lite.tbo](/lite.tbo/))
* See this <a href="http://ww1.microchip.com/downloads/en/AppNotes/AN-H53.pdf">application note</a> - recommend MD1213 and TC6320  (in [lite.tbo](/lite.tbo/))
* Possible (but not used in the end) high voltage source: https://datasheets.maximintegrated.com/en/ds/MAX5025-MAX5028.pdf (3 -&gt; 30V) to be used with a <a href="http://www.eleccircuit.com/the-many-dc-to-dc-converters-using-ic-555/">555 DC-DC convertor</a> (in [lite.tbo](/lite.tbo/))
* Signal back from the diod is clipped by <a href="http://ww1.microchip.com/downloads/en/DeviceDoc/MD0100.pdf">MD0100</a> + back to back diods.   (in [lite.tbo](/lite.tbo/))
* <a href="/lite.tbo/source/">Source files</a> (in [lite.tbo](/lite.tbo/))
* <a href="/lite.tbo/schematics.PDF">Schematics</a> (in [lite.tbo](/lite.tbo/))
* <a href="/lite.tbo/build/BOM.xls">BOM</a> (in [lite.tbo](/lite.tbo/))
* <a href="/lite.tbo/build/Gerbers_10_03_2018.zip">Gerbers</a> (in [lite.tbo](/lite.tbo/))
* <a href="/lite.tbo/build/odb.zip">ODB</a> (in [lite.tbo](/lite.tbo/))
* <a href="/lite.tbo/build/PickPlace_10_03_2018.zip">Pickplace</a> (in [lite.tbo](/lite.tbo/))
* Needs only 5V (in [lite.tbo](/lite.tbo/))
* HV: NMT0572SC (in [lite.tbo](/lite.tbo/))
* Pulser : MD1213 and TC6320 -&gt; see <a href="http://ww1.microchip.com/downloads/en/AppNotes/AN-H53.pdf">Fig.6 here, bipolar 3 level pulser</a>. (in [lite.tbo](/lite.tbo/))
* <a href="http://ww1.microchip.com/downloads/en/DeviceDoc/tc6320.pdf">TC6320, undamped</a>, detailed here.  (in [lite.tbo](/lite.tbo/))
* TC6320 http://ww1.microchip.com/downloads/en/DeviceDoc/20005697A.pdf for the datasheet (in [lite.tbo](/lite.tbo/))
* Protection: MD0100+diods -- should be enough, see <a href="http://ww1.microchip.com/downloads/en/DeviceDoc/MD0100.pdf">bottom of page 1, or Fig 9</a> (in [lite.tbo](/lite.tbo/))
* Review a bipolar design (originally alt.tbo -- but double the components and hence the price) (in [lite.tbo](/lite.tbo/))


### Todos from worklog
* add Visa, possibly Pouya and Thomas as contributors
* map interested (green) 
* Add a documentation server
* Display IP on the OLED.
* Need to have a look at this RPI GPIO DMA - https://github.com/hzeller/rpi-gpio-dma-demo
* Include some cletus remarks (sourcing) on gitbook
* add some ideas for [the pulser](https://electronics.stackexchange.com/questions/212667/ultrasound-transducer-excitation-frequency-transistor-type?rq=1) to the alt.pulser board
* remove gitbook MD files from the log
* link to files in the log (python)
* Main readme as TPL
* test some compressed sensing using [golay codes](/include/20170325/PulseCode.pdf) on a single element piezo
* _senjak_ 15:07 In Which a PDF is a Git Repository Containing its own Latex Source and a Copy of Itself -- https://github.com/ESultanik/PDFGitPolyglot/blob/master/make_polyglot.sh
* 20171111a and 20171112b Readmes
* impedance matching -- [see more](/include/impedance/ipm.pdf) -- Butterworth-Van-Dyke or [here](https://electronics.stackexchange.com/questions/245915/picking-source-resistance-for-impedance-matching). [Tuning Filter](https://i.stack.imgur.com/96XMb.png).
* list other initiatives
* classifier articles with link Article: =)
* a page sumarizing the experiments (as in the __Experiments__ page in the gitbook)
* Brainstorm for @senjak information design:
* un0rick site to have plenty of stuff
 * Publish first drafts on un0rick GH / GH-pages / gitbook
* create v2 release once gob.v2 and corrected/working alt.tbo v2 are ready.
* use [General Design Procedure for Free and Open-Source Hardware for Scientific Equipment](http://www.mdpi.com/2411-9660/2/1/2/htm) as a reference
* compare [old pulser](/retired/alt.tbo/20171111a/20171111-pulses.ipynb) (pulser) and [new acs](/matty/20180224b/20180221b-Client.ipynb) for matty readme
 * for matty [Rip this intro?](https://qspace.library.queensu.ca/bitstream/handle/1974/6235/Wall_Kieran_A_201012_PhD.pdf?sequence=1&isAllowed=y)
* clean all repos for a v2 release of modules 
 * decrypt the connector =)
 * Script to check IMGs URL matches path
 * reorganise
Loved Nasa: add to un0rick
* change path of images when they have changed
* Create detailed pages for the community in the gitbook
* Create detailed pages for each probe [I've played with](/include/probes/Readme.md) in the gitbook
* add dp location
* listing experiments of others
* before reclean full repo, create release "Full Dev Resources" and get corresponding version (v1.9 + hash)!
 * : Add Full GitBook PDF to it before
* Sort the list of experiments, shortnames in SUMMARY
* Community: list the contributors in a page + add the experiment. Individual page to point to experiment.
* Page on documentation
* Edit [history](https://kelu124.gitbooks.io/echomods/content/Chapter1/history.html) page to add Matty.
* Rewrite the Chapters Readme -> "This chapter is dedicated to the brain_dumps "
* Do a Doj (LOW PRIORITY)
* Redo a usable alt.tbo (LOW PRIORITY)
* Clean Modules list (keep lite.tbo, goblin, cletus, doj, elmo, matty) + add "CNprobe"
 * Make 7 clean QuickStarts for remaining modules // copy them on Tindie.
 * Get "ShortNames" in JSON
* Put alt.tbo, tobo, loftus, tomtom, croaker, retroATL3 and wirephantom in retired modules + add "PU3090" phantoms in retired
* Remove sets in doc
* Remake homepage in autodoc
* Clean obsolete versions in repos




[](@autogenerated - invisible comment)