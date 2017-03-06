# Interested in a monoelement transducer for an open science project

## Letter

Dear XXX,

I'm currently working with an open-source echography association  (echopen.org) based in Paris, which is currently looking for transducers that could be used for medical imaging for the design of its tool. I have heard your name through former colleagues at the ESPCI Paristech, and would like to investigate if you could provide us with appropriate transducers for this project.
 
We are developing a mechanical, single-element-design probe, operating at three frequencies, so with three series of piezos, with the following details:

* One at 3.5 MHz, focal zone between 50 and 150 mm,
* One at 5 MHz , focal zone between 30 and 105 mm,
* One at 7.5 MHz , focal zone between 10 and 75 mm.

With respect to the dimensions, ideally, we are looking for a low-footprint transducer (less than 2 cm diameter) and minimal depth for the physical size of the transducer (we don't need casing, though we'd need the backing and soldering already done) to integrate in our prototype. We'll be finetuning additional parameters as soon as we make progress on the probe itself. we would need:

* Diameter: as small as possible, ideally below 15mm for the 3.5MHz, 8mm for the 5MHz and 5mm for the 7.5MHz - without casing.
* Thickness: as small as possible.

Would it be possible for you to provide us with a quote for a first, to test one, along with the corresponding specs? Also, even using rough figures, we'd be keen on having an idea of the budget that'd be required to produce a couple, from 2 or 3 to 50 at the prototyping stage.

Looking forward to reading from you,

Best regards,

X


## Q&A

### Q

1. How are you defining your focal zone:  - 6 dB pressure, or -6 dB pressure squared? 

Olympus NDT and others define this by -6 dB pressure, but the therapeutic IEC standard defines this by -6 dB pressure squared. If you’re using -6 dB pressure, here is what I would suggest:

    - 3.5 MHz x 15 mm diameter x 100 mm radius.  This reaches 47 to 148 mm, assuming free field modeling. 
    - 5.0 MHz x 10 mm diameter x 65 mm radius.  This reaches 30 to 98 mm, assuming free field modeling.
    - 7.5 MHz x 4 mm diameter x unfocused (flat).  This reaches 13 to 61 mm, assuming free field modeling. 

2. What are you bandwidth and sensitivity requirements? 
3. Will you require a matching network for each transducer to sustain sensitivity over the bandwidth?
4. What cable length do you require (wire length for both ground and signal)? 
5. Do you have any biocompatibility or sterilization requirements? 
6. Will this need to pass a hi-pot specification? 

### and A

1. Better with pressure square
2. Bandwidth around 2-2.5 MHz, sensitivity: max possible
3. Matching layer for water
4. Depend, let's say 100 mm on coaxial cable
5. Don't know medical norm
6. Maybe needed for medical norm don't know
