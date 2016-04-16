Yeayyy, creation of the page
============================

The EchoModules
---------------

### Brief

Mostly, the thing would be to separate the
[Murgen](Hardware (murgen-dev-kit) "wikilink") PCB in 4 different
modules (similar to the arduino trinket pro for example), so to have
them ready to be used on a stripboard which would have already headers.

The strips would have the 11 tracks as on the attached picture below.

There would be 3 modules :

-   HV+pulser+md0100
-   TGC+enveloppe
-   SPI ADC

(Two other modules, Alim, and controler, will be stripboard based)

Given that the boards would be separated, would it make sense to try
to \*\*design the PCBs to have only 2 layers PCB\*\* ? The width of the
PCBs would not really matter, only to be sure they'd fit on a strip
board. It would be interesting to have a form factor of the modules PCB
comparable to one trinket pro =)

#### Details about the modules

1\. HV+Pulser+MD0100 don't change. The module will need to have a SMA
connector (same as on existing board).

2\. AGC+enveloppe detector can remain the same. I just need to remove the
filter that is between the TestPoints4 and 5 and the transformer. The
module output is the output of the ADL5511.

3\. SPI can be replaced, this one was an overkill. 10Msps is too much, so
instead a 2 or 3 Msps at 12 or 14 bits in SPI could be used on the ADC
module.

#### Controls

The "controls" listed would be a potentiometer for the HV (as was done
for murgen), a potentiometer for the TGC Gain (not an ADC, bit of
overkill, rather a jumper to allow one to select the gain from either
the track or a potentiometer which would feed in from 0 to 1V).

#### ADC details

The ADC can be as low as 12bits 2Msps when we're talking about envelope
detection (what about MAX11105?). (btw, the signal output by it is
offset by around 1.32V) on top of which we have 1.25V of signal. For the
sake of the experiment, I would add another ADC board, clone of the
11105, with a MAX11103, to comparatively test both.

#### The motherboard

-   what is expected is to break down logic blocks into modules that
    could be put on a motherboard ( a 2.54mm stripboard), max 20 to 24
    track wide.
    -   it appears 19 tracks would be good

##### Tofs

![](motherboard.png "motherboard.png")

![](cartes.png "cartes.png")

##### Table of tracks

       Name of module -\>           HV Module                                    TGC Module                                                                                                                                                                                                                                                                                                      ADC Module   Controller Module
  ---- ---------------------------- -------------------------------------------- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- ------------ ------------------- ----- ---- ----- ---- -----
       **Name of track**            **Signal id**                                In                                                                                                                                                                                                                                                                                                              Out          In
  1    Analog Gain                  SIG-gain                                                                                                                                                                                                                                                                                                                                                                  X
  2    Pulser On (Logic)            SIG-pulser\_on                               X                                                                                                                                                                                                                                                                                                                            
  3    Pulser Off (Logic)           SIG-pulser\_off                              X                                                                                                                                                                                                                                                                                                                            
  4    5V                           SIG-5v                                       X                                                                                                                                                                                                                                                                                                                            X
  5    3.3V                         SIG-3\_3v                                                                                                                                                                                                                                                                                                                                                                 X
  6    GND                          SIG-gnd                                      X                                                                                                                                                                                                                                                                                                                            X
  7    Raw Signal                   SIG-raw\_signal                              8 post TGC without enveloppe SIG-amplified\_signal X X 9 post TGC with enveloppe SIG-signal\_enveloppe X X 10 Angle SIG-abs\_motor\_angle X 11 Motor PWM or Stepper B2 SIG-cc\_motor\_pwm xor SIG-stepper\_b2 X 12 Stepper B1 SIG-stepper\_b1 X 13 Stepper A1 SIG-stepper\_a1 X 14 Stepper A2 SIG-stepper\_a2   X            X
  8    post TGC without enveloppe   SIG-amplified\_signal                                                                                                                                                                                                                                                                                                                                                     
  9    post TGC with enveloppe      SIG-signal\_enveloppe                                                                                                                                                                                                                                                                                                                                                     
  10   Angle                        SIG-abs\_motor\_angle                                                                                                                                                                                                                                                                                                                                                     
  11   Motor PWM or Stepper B2      SIG-cc\_motor\_pwm **xor** SIG-stepper\_b2                                                                                                                                                                                                                                                                                                                                
  12   Stepper B1                   SIG-stepper\_b1                                                                                                                                                                                                                                                                                                                                                           
  13   Stepper A1                   SIG-stepper\_a1                                                                                                                                                                                                                                                                                                                                                           
  14   Stepper A2                   SIG-stepper\_a2                                                                                                                                                                                                                                                                                                                                                           
  15   -5V                                                                                                                                                                                                                                                                                                                                                                                                    
  16   12V                                                                                                                                                                                                                                                                                                                                                                                                    
  17   -12V                                                                                                                                                                                                                                                                                                                                                                                                   
  18   18V                                                                                                                                                                                                                                                                                                                                                                                                    
  19   -3V                                                                                                                                                                                                                                                                                                                                                                                                    
  20   encodeur                                                                                                                                                                                                                                                                                                                                                                                               

### A rough draft

#### Table

       Name of module -\>           HV Module                                    TGC Module   ADC Module   Controller Module
  ---- ---------------------------- -------------------------------------------- ------------ ------------ ------------------- ----- ---- ----- ---- -----
       **Name of track**            **Signal id**                                In           Out          In
  1    Analog Gain                  SIG-gain                                                               X
  2    Pulser On (Logic)            SIG-pulser\_on                               X                         
  3    Pulser Off (Logic)           SIG-pulser\_off                              X                         
  4    5V                           SIG-5v                                       X                         X
  5    3.3V                         SIG-3\_3v                                                              X
  6    GND                          SIG-gnd                                      X                         X
  7    Raw Signal                   SIG-raw\_signal                                           X            X
  8    post TGC without enveloppe   SIG-amplified\_signal                                                  
  9    post TGC with enveloppe      SIG-signal\_enveloppe                                                  
  10   Angle                        SIG-abs\_motor\_angle                                                  
  11   Motor PWM or Stepper B2      SIG-cc\_motor\_pwm **xor** SIG-stepper\_b2                             
  12   Stepper B1                   SIG-stepper\_b1                                                        
  13   Stepper A1                   SIG-stepper\_a1                                                        
  14   Stepper A2                   SIG-stepper\_a2                                                        

#### Pic

![](Module_v3_0278.JPG "Module_v3_0278.JPG")

Worklog
-------

### April 5th

Validation of the approach by the Captech

### April 8th

Validation of tracks of interest
