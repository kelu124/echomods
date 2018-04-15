## Ultrasound hardware structure

[](@description Short description of the organization of modules)

To produce an image, the modules have to create a [high voltage pulse](/retired/tobo/), which excites a [transducer](/retroATL3/). Echoes coming from the body are amplified using a [TGC + LNA](/goblin/), which cleans the analog signal, which itself [gets digitalized](/retired/toadkiller/). 

The diagram is represented below:

![](/include/images/blockdiagram.gif)


